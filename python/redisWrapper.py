"""
    this just a wrapper class of redis.
"""

import redis, logging

class redisWrapper:
    # ensures that the connection is alive

    def __init__(self, host='localhost', port=6379, db=0, password=None, connection_pool=None):
        try:
            self.conn = redis.StrictRedis(host=host, port=port, db=db, password=password, connection_pool=connection_pool)
        except:
            logging.error('Failed to connect to Redis on %s', host)

    def push_list(self, key, value):
        try:
            self.conn.lpush(key, value)
        except:
            logging.error('Push failed.Establish a valid connection first!')

    def set_expire_time(self, key, seconds):
        try:
            self.conn.expire(key, seconds)
        except:
            logging.error('Set failed.Establish a valid connection first!')

    def get_value(self, key):
        # input the key, return all the value
        try:
            return self.conn.lrange(key, start=0, end=self.conn.llen(key))
        except:
            logging.error('Get failed.Establish a valid connection first!')
            return

    def save_redis(self):
        try:
            return self.conn.save()
        except:
            logging.error('Save failed.Establish a valid connection first!')
            return
