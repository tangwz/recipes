# 操作系统试题：
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
