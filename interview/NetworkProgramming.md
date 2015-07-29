# 网络编程试题：
### 1、字符串"Hello"会被输出几次？

下面代码的字符串"Hello"会被输出几次?
```
int main() {
 printf("Hello");
 fork();
 printf("Hello");
}
```
正确答案：4次。

回答三次的同学，可以看看这篇文章：http://coolshell.cn/articles/7965.html
