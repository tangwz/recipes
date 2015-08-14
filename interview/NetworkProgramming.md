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

### 2、大端和小端。

a) Little-Endian就是低位字节排放在内存的低地址端， 高位字节排放在内存的高地址端。

b) Big-Endian就是高位字节排放在内存的低地址端，低位字节排放在内存的高地址端。

c) 网络字节序：TCP/IP各层协议将字节序定义为Big-Endian，因此TCP/IP协议中使用的字节序通常称之为网络字节序。

假设整数0x12345678 存放在内存地址0x0开始的连续四个字节中 (即地址0x0到 0x3)。

如果是 Little-Endian：0x0-0x3内存分别存放的是：0x78、0x56、0x34、0x12；

如果是  Big-Endian ：0x0-0x3内存分别存放的是：0x12、0x34、0x56、0x78； 

