## recipes -- python notes
### python
__python中WSGI的底层原理和作用，和CGI有何关联和区别？__

日常处理需经常用到的模块：
```
time、os、sys、datetime、ConfigParser、subprocess、logging、re
```
进阶必学模块如下：
```
itertools、functools、collections、operator、toolz、cytoolz
```
数据库相关模块：
```
json、pymongo、sqlite
```
追求效率与速度
```
numpy、pandas
```
最后，加深对迭代器、生成器、装饰器的理解；

定制类：

 - ```__str__```
 - ```__slots__```
 - ```__len__```
 - ```__iter__```
 - ```__getitem__```
 - ```__setitem__```
 - ```__reversed__```
 - ```__getattr__```
 - ```__setattr__```
 - ```__call__```

第三方模块：
 - jon：http://jonpy.sourceforge.net/，用来处理CGI
 - requests：http://www.python-requests.org/en/latest/，给人类使用的HTTP库！

### Flask
 - flask用来做后台，一个坑是request.form和request.json，一个处理表单，一个处理json，为什么坑呢？因为flask在这里会检查HTTP Header中application的类型（这个年代还要检查Content-Type）。需要弄清楚前段发过来的消息格式，谨慎选择使用。
 - flask的一些装饰器
