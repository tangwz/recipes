# interview

笔试、面试常遇到的问题：

目录：
 - 语言无关类：
   - [算法与数据结构](#算法与数据结构)
   - [操作系统](#操作系统)
   - [网络编程](#网络编程)
   - [数据库](#数据库)
 - 语言相关类：
   - [C/C++](#cc)
   - JAVA
   - Python

## 算法与数据结构：
### problem 1：
```
堆排序的空间复杂度是（），堆排序中构建堆的时间复杂度是():
A.O(logn)，O(n)
B.O(logn)，O(nlogn)
C.O(1)，O(n)
D.O(1)，O(nlogn)
```
“空间复杂度”指占内存大小，堆排序每次只对一个元素操作，是就地排序，所用辅助空间O(1)，空间复杂度是O（1）。

在构建堆的过程中，完全二叉树从最下层最右边的非终端结点开始构建，将它与其孩子进行比较和必要的互换，对于每个非终端结点来说，其实最多进行两次比较和互换操作，因此整个构建堆的时间复杂度为O(n)。

在正式排序时，第i次取堆顶记录重建堆需要用O(logi)的时间（完全二叉树的某个结点到根结点的距离为⌊log2i⌋+1），并且需要取n-1次堆顶记录，因此，重建堆的时间复杂度为O(nlogn)。

### problem 2：
若用一个大小为6的数组来实现循环队列，且当前rear和front的值分别0和3。当从队列中删除一个元素，再加入两个元素后，rear和front的值分别为（）
```
A.2和4
B.1和5
C.4和2
D.5和1
```
删除一个元素后，队首指针要加1，front=（front+1）%6，结果为4，每加入一个元素队尾指针加一，即real=（real+1）%6，加入两个元素后变为2，所以选A.

**对6取余是为了实现循环队列，构成一个环！**

## 操作系统：

### 基础：
 - linux进程模型、进程/线程区别；
 - 堆/栈的区别，大概的位置，各往哪个方向生长，各类变量存储在哪些区域；
 - 更深一点可能会问动态库与静态库的区别，因为这个在生产环境中常见，动态库映射在进程模型的哪里；
 - 其他常见如僵尸进程、线程共享等问题。

### problem 1：
```
以下哪些线程同步锁可以为递归锁：
1.信号量  2.读写锁   3.互斥量   4.事件   5.临界区（Critical Section）

A.1，3，4，5
B.5
C.3，5
D.1，3，5
```
常见的进程/线程同步方法有互斥锁（或称互斥量Mutex）、读写锁（rdlock）、条件变量（cond）、信号量（Semophore）等。

在windows系统中，临界区（Critical Section）和事件对象（Event）也是常用的同步方法。

**递归锁/非递归锁**
Mutex可以分为递归锁（recursive mutex）和非递归锁（non-recursive mutex）。 递归锁也叫可重入锁（reentrant mutex），非递归锁也叫不可重入锁（non-reentrant mutex）。

二者唯一的区别是：

同一个线程可以多次获取同一个递归锁，不会产生死锁。

如果一个线程多次获取同一个非递归锁，则会产生死锁。

**Windows下的Mutex和Critical Section是可递归的。**

**Linux下的pthread_mutex_t锁是默认是非递归的。可以通过设置PTHREAD_MUTEX_RECURSIVE属性，将pthread_mutex_t锁设置为递归锁。**

## 网络编程：

### TCP/IP基础：
 - 常问三次握手，四次挥手，为什么要四次；
 - time_wait状态相关问题；
 - mtu分片问题；
 - 可能会问tcp头部几个状态字段，比如syn/psh/fin/rst/urg/ack....在什么情形下会置1；
 - 滑动窗口与流量控制、拥塞控制的大致原理。

### Socket编程：
 - 阻塞/非阻塞、同步/异步、进程池/线程池、串行化/持久化的区别；
 - 事件循环select/poll/epoll（epoll为什么高效）；
 - 常见的网络库read/write会怎样实现（可以参考muduo）；
 - 可能会问客户端是否需要bind；
 - tcp/udp协议编程时的细微区别。

## 数据库：


## C/C++:

### 开发工具：
 - 编译器：gcc/g++、makefile；
 - 调试工具：gdb；
 - 内存泄露检查：valgrind；
 - 文档组织工具：doxygen；

### 白板编程：

1. 实现STL中的vector，vector容量扩张过程（是否原地扩张）；
2. 实现STL中的string；
3. 实现STL中的stack；
4. *实现其他STL容器，例如map、hash等（概率不大）*；
4. 灵活应用virtual继承+shared_ptr；

### C problem 1：
```
#include <stdio.h>

int main()
{
	int a[5] = {1, 2, 3, 4, 5};
	int *ptr = (int*)(&a + 1);
	printf("%d,%d\n", *(a + 1), *(ptr - 1));
	return 0;
}
```
对指针进行加1 操作，得到的是下一个元素的地址，而不是原有地址值直接加1。所以，一个类型为T的指针的移动，以sizeof(T)为移动单位。因此，对上题来说，a 是一个一维数组，数组中有5 个元素； ptr 是一个int 型的指针。

&a + 1: 取数组a 的首地址，该地址的值加上sizeof(a)的值，即&a+5*sizeof(int)，也就是下一个数组的首地址，显然当前指针已经越过了数组的界限。

(int *)(&a+1): 则是把上一步计算出来的地址，强制转换为int * 类型，赋值给ptr。

*(a + 1): *(a + 1)其实等于a[1]，这里是个语法糖。

由此可见，&a[0], &a, a 三者的值相同（意义不同）； &a + 1与&a 差5个字节， 即5 * sizeof(int);

**C语言中有一个著名的“语法糖”**，即a[i]和a[i][j]，在这里用a[i]表示\*(a+i),用a[i][j]表示\*(\*(a+i\*数组a第二维的长度)+j)，这样使人容易理解，当然也催生了一堆的面试笔试题。

### C problem 2：
```
void func(char str_arg[100])
{
     cout<<sizeof(str_arg)<<endl;
}
int main(int argc,char* argv[])
{
     char str[]="Hello";
     char *p=str;
     cout<<sizeof(str)<<endl;
     cout<<sizeof(p)<<endl;
     func("test");
     return 0;
}
```
sizeof对数组求长度为数组的真实长度，字符串数组的长度要加上最后的'\0'字符。64位机器的指针占8个字节。

sizeof(str)测量的是字符数组的占用长度，注意字符串后还有个\0，所以是6;

sizeof(p)测量的是指针的占用长度，64位系统下是8字节;

sizeof(str_arg)测量的是指针长度，因为这里是形参;

**sizeof()**还有很多情况，比如`sizeof(结构体)`、`sizeof(二维数组各种情况)`、`sizeof(空结构体、空类、空联合体)`等等非常特殊的情况，例如：
```
double* (*a)[3][6]; 
cout<<sizeof(a)<<endl; // 4 a为指针
cout<<sizeof(*a)<<endl; // 72 *a为一个有3*6个指针元素的数组
cout<<sizeof(**a)<<endl; // 24 **a为数组一维的6个指针
cout<<sizeof(***a)<<endl; // 4 ***a为一维的第一个指针
cout<<sizeof(****a)<<endl; // 8 ****a为一个double变量

struct s0{

};

union u0{

};

struct s1
{
char a;
double b;
int c;
char d;
};

struct s2
{
char a;
char b;
int c;
double d;
};

class c0{};

cout<<sizeof(s0)<<endl;//1
cout<<sizeof(u0)<<endl;//1
cout<<sizeof(s1)<<endl;//24
cout<<sizeof(s2)<<endl;//16
cout<<sizeof(c0)<<endl;//1
```
**这里涉及很多情况讨论，请自行谷歌。**

### C problem 3：
下面说法正确的是（）

A.++已有的任何运算符都可以重载

B.const对象只能调用const类型成员函数

C.构造函数和析构函数都可以是虚函数

D.函数重载返回值类型必须相同

A 不能重载‘.’，因为‘.’在类中对任何成员都有意义，已经成为标准用法；

  不能重载 ?: ，因为这个运算符对于类对象来说没有实际意义，相反还会引起歧义； 
  
  还有：：。
  
C 构造函数，不能是虚函数。 

D 函数重载只跟**参数类型**和**参数个数**有关。

### C problem 4：
```
有如下程序段：
class A
{
    public:
        A()
        {
            printf(“0”);
        }
        A(int a)
        {
            printf(“1”);
        }
        A& operator=(const A& a)
        {
            printf(“2”);
            return*this;
        }
}
int main()
{
    A al;
    al=10;
}
则程序输出是：
A.02
B.012
C.01
D.以上都不对
```
A a1; //调用A默认构造函数

a1=10; //类型不匹配，调用构造函数A(int)进行隐式转化，之后将引用传给operator=（）
