# interview

笔试、面试常遇到的问题。
## C/C++:

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

###C problem 2：
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
