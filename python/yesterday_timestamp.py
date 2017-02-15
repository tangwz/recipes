# coding: utf-8
import time
import datetime


yesterday = datetime.datetime.now() - datetime.timedelta(days = 1)
yesterday_beginning = datetime.datetime(yesterday.year, yesterday.month, yesterday.day,0,0,0,0)
yesterday_beginning_time = int(time.mktime(yesterday_beginning.timetuple()))
yesterday_end = datetime.datetime(yesterday.year, yesterday.month, yesterday.day,23,59,59,999)
yesterday_end_time = int(time.mktime(yesterday_end.timetuple()))

print yesterday_beginning_time
print yesterday_end_time
