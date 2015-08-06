# C/C++相关试题：
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

### C problem 5：

```
下列代码的输出为：
class CParent 
{
    public: virtual void Intro()
    {
        printf( "I'm a Parent, " ); Hobby();
    }
    virtual void Hobby()
    {
        printf( "I like football!" );
    }
}; 
class CChild : public CParent { 
    public: virtual void Intro()
    {
        printf( "I'm a Child, " ); Hobby();
    }
    virtual void Hobby()
    {
       printf( "I like basketball!\n" );
    }
}; 
int main( void )
{
    CChild *pChild = new CChild(); 
    CParent *pParent = (CParent *) pChild; 
    pParent->Intro(); 
    return(0);
}

A. I'm a Parent， I like football!

B. I'm a Parent， I like basketball!

C. I'm a Child， I like basketball!

D. I'm a Child， I like football!
```
输出：I’m a Child, I like basketball!

这题动态联编，Intro()和Hobby()都是虚函数且通过指针调用，基类指针会向派生类中寻找，找到后执行派生类的函数，所以输出的结果是I’m a Child, I like basketball!

参考：[C++虚函数及虚函数表解析](http://www.cnblogs.com/chinazhangjie/archive/2012/07/11/2586535.html)。

另：(CParent *)这个要不要都没关系的。

### C problem 6：
```
下述有关c++的虚类和java接口的描述，说法错误的是？
A. c++虚类相当与java里面的抽象类
B. c++中没有接口的概念，与之对应的是纯虚类，对应的是java的借口
C. 纯虚函数和虚函数的区别在于前者不包含定义，而后者可以包含函数体。
D. 一个抽象类和接口中的方法必须是抽象方法
```
选D.

抽象类 ： 类中至少有一个方法是抽象方法，则该类就是抽象类；

接口 ：类中的方法全部都是抽象方法。

抽象类和接口的其它特点：
 - 一个子类只能继承一个抽象类（虚类），但能实现多个接口；
 - 一个抽象类可以有构造方法，接口没有构造方法；
 - 一个抽象类中的方法不一定是抽象方法，即其中的方法可以有实现（有方法体），接口中的方法都是抽象方法，不能有方法体，只有声明；
 - 一个抽象类可以是public、private、protected、default，接口只有public;
 - 一个抽象类中的方法可以是public、private、protected、default，接口中的方法只能是public和default。
