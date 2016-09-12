-- Issues:
--     timeout值需要设置得比较久，否则偶尔会get不到master
--
-- local redis_conn = require "connector"
-- local rc = redis_conn.new()
-- rc:set_connect_timeout(10)
--
-- local sentinel, err, previous_errors = rc:connect_sentinel{
--     sentinels = {
--         { host = "10.160.93.118", port = 26379 },
--         { host = "10.160.93.119", port = 26379 },
--         { host = "10.160.93.120", port = 26379 },
--     },
--     db = 3,
-- }
--
-- if not sentinel then
--     ngx.log(ngx.ERR, err)
-- end

local redis = require "resty.redis"
redis.add_commands("sentinel")
local sentinel = require "sentinel"

local ok, new_tab = pcall(require, "table.new")
if not ok then
    new_tab = function (narr, nrec) return {} end
end

local _M = {
    _VERSION = '1.0',
}

local mt = {__index = _M}

function _M.new()
    return setmetatable({
        connect_timeout = 10,
        connection_options = nil, -- pool, etc
    }, mt)
end

function _M.set_connect_timeout(self, timeout)
    self.connect_timeout = timeout
end

function _M.set_connection_options(self, options)
    self.connection_options = options
end


function _M.connect_sentinel(self, params)
    if not params or type(params) ~= "table" then
        params = {}
    end

    local sentinels = params.sentinels
    local db = params.db

    for i, s in ipairs(sentinels) do
        s.db = db
    end
    return self:try_hosts(sentinels)
end

function _M.try_hosts(self, hosts)
    local errors = new_tab(#hosts, 0)

    for i, host in ipairs(hosts) do
        local res
        res, errors[i] = self:connect_to_host(host)
        if res then
            return res, table.remove(errors), errors
        end
    end
    return nil, table.remove(errors), errors
end

function _M.connect_to_host(self, host)
    local red = redis.new()
    red:set_timeout(self.connect_timeout)

    local ok, err
    if self.connection_options then
        ok, err = red:connect(host.host, host.port, self.connection_options)
    else
        ok, err = red:connect(host.host, host.port)
    end

    if not ok then
        ngx.log(ngx.ERR, err)
        return nil, err
    else
        -- 如有需要，可以在这里添加密码验证
        red:select(host.db)
        return red, nil
    end
end

return _M
