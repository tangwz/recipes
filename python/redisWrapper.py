# -*- coding:utf-8 -*-
"""
    this just a easy wrapper class of redis.
    version 2.0, by tangwz.
"""


import redis, logging

class redisWrapper:
    # ensures that the connection is alive

    def __init__(self, host='localhost', port=6379, db=0, password=None, socket_timeout=None, connection_pool=None):
        try:
            self.conn = redis.StrictRedis(host=host, port=port, db=db, password=password, socket_timeout=socket_timeout, connection_pool=connection_pool)
        except:
            logging.error('Failed to connect to Redis on %s', host)

    def get_keys(self, pattern='*'):
        # returns a list of keys matching pattern
        try:
            return self.conn.keys(pattern)
        except:
            logging.error('Get keys failed.Establish a valid connection first!')
            return

    def delete_key(self, names):
        # delete one or more keys specified by names
        try:
            return self.conn.delete(names)
        except:
            logging.error('Delete keys failed.Establish a valid connection first!')
            return

    def set_string(self, key, value):
        try:
            self.conn.set(key, value)
        except Exception as e:
            logging.error('Set string failed.Establish a valid connection first!')

    def get_string(self, key):
        try:
            return self.conn.get(key)
        except:
            logging.error('Get string failed.Establish a valid connection first!')
            return

    def push_list(self, key, value):
        # push the value to the head of the list
        try:
            self.conn.lpush(key, value)
        except:
            logging.error('Push list failed.Establish a valid connection first!')

    def get_list(self, key):
        # input the key, [warning]return all the value!
        try:
            return self.conn.lrange(key, start=0, end=self.conn.llen(key))
        except:
            logging.error('Get list failed.Establish a valid connection first!')
            return

    def del_elem(self, key, count, value):
        # Remove the first count occurrences of elements equal to value from the list stored at key.
        try:
            return self.conn.lrem(key, count, value)
        except:
            logging.error('Delelte element failed.Establish a valid connection first!')
            return 0

    def set_expire_time(self, key, seconds):
        try:
            self.conn.expire(key, seconds)
        except:
            logging.error('Set expire time failed.Establish a valid connection first!')

    def get_expire_time(self, key):
        try:
            return self.conn.ttl(key)
        except:
            logging.error('Get expire time failed.Establish a valid connection first!')
            return

    def save_redis(self):
        try:
            return self.conn.save()
        except:
            logging.error('Save failed.Establish a valid connection first!')
            return
