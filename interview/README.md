# interview

笔试、面试常遇到的问题：

目录：
 - 语言无关类：
   - [算法与数据结构](#算法与数据结构)
   - [操作系统](#操作系统)
   - [网络编程](#网络编程)
   - [数据库](#数据库)
   - [设计模式](#设计模式)
 - 语言相关类：
   - [C/C++](#cc)
   - JAVA
   - Python

## 算法与数据结构：
### 数据结构：
 - 线性：数组，**链表**，**队列**，**堆栈**，**hash表**，块状数组（数组+链表），双端队列，位图（bitmap）；
 - 树：**堆（大顶堆、小顶堆）**，trie树（字母树or字典树），后缀树，后缀树组，**二叉排序/查找树**，**B+/B树**，AVL树，Treap，**红黑树**，splay树，线段树，树状数组；
 - 图：有向图，无向图；
 - 其它：并查集；

### 算法：
 - **基本思想**：枚举，递归，分治，贪心，动态规划，回溯；
 - 图算法：**深度优先遍历与广度优先遍历**，最短路径，最小生成树，拓扑排序；
 - 字符串算法：字符串查找，hash算法，KMP算法；
 - 排序算法：冒泡，插入，选择，快排，归并排序，堆排序，桶排序；
 - 数论问题：素数问题，整数问题，进制转换，同余模运算；

**[算法与数据结构相关试题](./Datastructure&Algorithm.md)**

## 操作系统：

### 基础：
 - linux进程模型、进程/线程区别；
 - 堆/栈的区别，大概的位置，各往哪个方向生长，各类变量存储在哪些区域；
 - 更深一点可能会问动态库与静态库的区别，因为这个在生产环境中常见，动态库映射在进程模型的哪里；
 - 其他常见如僵尸进程、线程共享等问题。

**[操作系统相关试题](./OS.md)**

### 资料：
 - Linux内存管理基本概念：http://vmlinz.is-programmer.com/posts/26540.html

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

**[网络编程相关试题](./NetworkProgramming.md)**

## 数据库：

## 设计模式：

## C/C++:

### C++ 11的了解：
 - Lambda：[capture](parameters)->return_type {body}
 - 可变参数模板（ Variadic templates）：https://www.chenlq.net/books/cpp11-faq/cpp11-faq-chinese-version-series-variadic-templates.html
 - 自动类型推导 auto：
 - 自动化推导 decltype：
 - constexpr：
 - nullptr：
 - 智能指针：shared_ptr 、unique_ptr、weak_ptr；
 - 列表初始化：
 - 正则表达式：
 - STL线程库：
 - 静态断言（static_assert）：断言有一个问题，就是一定会abort，强制整个程序退出而导致调试也无法继续进行。static_assert就是在编译时就能够进行检查的断言。
 - 委托构造：https://www.chenlq.net/books/cpp11-faq/cpp11-faq-chinese-version-series-delegate-constructors.html
 - 右值引用和move语义：对某个stirng的右值引用可以单纯地从右值复制其内部C-style的指针到新的string，然后留下空的右值。这个操作不需要内存数组的复制，而且空的暂时对象的析构也不会释放内存。其更有效率。

更多：
 - (C++ 11 FAQ中文版)[https://www.chenlq.net/cpp11-faq-chs]
 - (C++ 11 FAQ)[http://www.stroustrup.com/C++11FAQ.html]

### 开发工具：
 - 编译器：gcc/g++、makefile；
 - 调试工具：gdb；
 - 内存泄露检查：valgrind；
 - 文档组织工具：doxygen；

### 白板编程：

_如有时间可自己实现一个mini STL_

1. 实现STL中的vector，vector容量扩张过程（是否原地扩张）；
2. 实现STL中的string；
3. 实现STL中的stack；
4. *实现其他STL容器，例如map、hash等（概率不大）*；
4. 灵活应用virtual继承+shared_ptr；

**[C/C++相关试题](./CC.md)**

### 资料：
- 虚函数原理：http://www.learncpp.com/cpp-tutorial/125-the-virtual-table/
- this指针原理：http://www.bogotobogo.com/cplusplus/this_pointer.html
- 类的sizeof：http://blog.csdn.net/pizi0475/article/details/6292556
- 根据成员变量的指针获取结构体变量的指针：http://en.wikipedia.org/wiki/Offsetof
- C语言扩展：http://www.kerneltravel.net/newbie/gcc_man.html#5.7
- C语言常用宏定义：http://www.cnitblog.com/zouzheng/archive/2007/08/31/32691.aspx
- C中的MIN，MAX宏实现：http://blog.csdn.net/snowbabybw/article/details/6120780
