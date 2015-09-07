__author__ = 'tangwz'
# -*- coding: utf-8 -*-

import urllib2
import time
from threading import Thread

class GetUrlThread(Thread):
    def __init__(self, url):
        self.url = url
        super(GetUrlThread, self).__init__()

    def run(self):
        resp = urllib2.urlopen(self.url)
        print self.url, resp.getcode()

def get_responses():
    urls = [
        'http://www.baidu.com',
        'http://www.amazon.com',
        'http://www.zhihu.com',
        'http://www.alibaba.com',
        'http://www.qq.com'
    ]
    start = time.time()
    threads = []
    for url in urls:
        t = GetUrlThread(url)
        threads.append(t)
        t.start() # exec run()
    for t in threads:
        t.join()  # join()可以通知主线程等待这个线程结束后，才可以执行下一条指令。
    # 每个线程我们都调用了join()方法，所以我们是在所有线程执行完毕后计算的运行时间。
    print "Elapsed time: %s" % (time.time() - start)

# cpu可能不会在调用start()后马上执行run()方法。
# 你不能确定run()在不同线程建间的执行顺序。
# 对于单独的一个线程，可以保证run()方法里的语句是按照顺序执行的。
# 这就是因为线程内的url会首先被请求，然后打印出返回的结果。
get_responses()