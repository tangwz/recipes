# coding: utf-8

'''
  __author__ = 'the5fire'
  http://www.the5fire.com/python-time2timestamp.html
'''

import time

def time2stamp(timestr, format_type='%Y-%m-%d %H:%M:%S'):
    return time.mktime(time.strptime(timestr, format_type))

def stamp2time(stamp, format_type='%Y-%m-%d %H:%M:%S'):
    return time.strftime(format_type, time.localtime(stamp))

if __name__ == '__main__':
    tt = time.time()
    nowtime = stamp2time(tt)
    print nowtime
    tt = time2stamp(nowtime)
    print tt
    
