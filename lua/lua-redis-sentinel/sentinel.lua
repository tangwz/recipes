-- local redis_sentinel = require "sentinel"
-- local master, err = redis_sentinel.get_master(redis, "master_name")
-- if not master then
--     ngx.say(err)
-- else
--     ngx.say("host: ", master.host)
--     ngx.say("port: ", master.port)
-- end

local ok, new_tab = pcall(require, "table.new")
if not ok then
    new_tab = function (narr, nrec) return {} end
end

local _M = {
    _VERSION = '1.0',
}

function _M.get_master(sentinel, master_name)
    if sentinel == nil then
        return nil, "sentinel is nil"
    end
    local res, err = sentinel:sentinel(
        "get-master-addr-by-name",
        master_name
    )
    if res and res ~= ngx.null and res[1] and res[2] then
        return { host = res[1], port = res[2] }
    else
        return nil, err
    end
end


return _M
