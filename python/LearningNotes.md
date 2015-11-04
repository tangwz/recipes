## recipes -- python notes

```
from ... import ...

class XXX(XXX):
  def __init___(self, ...):
    super(XXX, slef).__init__(...)
    self._xxx = xxx

  def method(...):
    ...
```

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
追求效率与速度（写c扩展的模块，我还没达到这能力，自行谷歌）
```
numpy、pandas
```
最后，加深对迭代器、生成器的理解；

定制类：

 - __str__
 - __slots__
 - __len__
 - __iter__
 - __getitem__
 - __setitem__
 - __reversed__
 - __getattr__
 - __setattr__
 - __call__

遇到的问题：
 - jon的使用：http://jonpy.sourceforge.net/，用来处理CGI
