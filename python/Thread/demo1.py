__author__ = 'tangwz'
# -*- coding: utf-8 -*-

import time
import urllib2

# Single threaded way
def get_response():
    urls = [
        'http://www.baidu.com',
        'http://www.amazon.com',
        'http://www.zhihu.com',
        'http://www.alibaba.com',
        'http://www.qq.com'
    ]
    start = time.time()
    for url in urls:
        print url
        resp = urllib2.urlopen(url)
        print resp.getcode()
    print "Elapsed time: %s" % (time.time() - start)

get_response()