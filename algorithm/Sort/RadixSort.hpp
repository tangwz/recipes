/*
 * Algorithm--RadixSort：https://en.wikipedia.org/wiki/Radix_sort
 * 
 */

/* 由于整数也可以表达字符串（比如名字或日期）和特定格式的浮点数，所以基数排序也不是只能使用于整数。 */
/* 基数排序的方式可以采用LSD（Least significant digital）或MSD（Most significant digital）。 */
/* LSD的排序方式由键值的最右边开始，而MSD则相反，由键值的最左边开始。 */
/* 时间复杂度是O(k·n) */

#include <stdio.h>

/* 关键字基数，此时是十进制 */

#define R 10 /* Radix */

 /**
  * @struct
  * @brief 静态链表结点
  */

typedef struct  static_list_node_t{
	int key;/* 关键字 */
	int link;/* 下一个节点 */
}static_list_node_t;

/*
 * @brief 打印静态链表
 * @param[in] a 静态链表数组
 * @return None
 */
static void static_list_print(const static_list_node_t a[])
{
	int i = a[0].link;
	while(i != 0){
		printf("%d ", a[i].key);
		i = a[i].link;
	}
}

/*
* @brief 获取十进制整数的某一位数字.
* @param[in] n 整数
* @param[in] i 第 i 位
* @return 整数 n 第 i 位的数字
*/
static int get_digit(int n, const int i)
{
	int j;
	for(j = 1; j < i; j++){
		n /= 10;
	}

	return n % 10;
}

/**
* @brief LSD 链式基数排序.
* @param[in] a 静态链表， a[0] 是头指针
* @param[in] n 待排序元素的个数
* @param[in] d 最大整数的位数
* @return 无
* @note 无
* @remarks 无
*/
void radix_sort(static_list_node_t a[], const int n, const int d)
{
	int i, j, k, current, last;
	int rear[R], front[R];

	for(i = 0; i < n; ++i) a[i].link = i + 1;
	a[n].link = 0;
	for(int i = 0; i < d; ++i){
		/* 分配 */
		for(j = 0; j < R; ++j) front[j] = 0;
		for(current = a[0].link; current != 0; current = a[current].link){
			k = get_digit(a[current].key, i + 1);
			if(front[k] == 0){
				front[k] = current;
				rear[k] = current;
			}else{
				a[rear[k]].link = current;
				rear[k] = current;
			}
		}

		/* 收集 */
		j = 0;
		while(front[j] == 0) j++;
		a[0].link = current = front[j];
		last = rear[j];
		for(j = j + 1; j < R; ++j){
			if(front[j] != 0){
				a[last].link = front[j];
				last = rear[j];
			}
		}
		a[last].link = 0;
	}
}

void radix_sort_rest(void){
	static_list_node_t a[] = {{0,0}/* 头指针 */, {278,0}, {109,0},
	{63,0}, {930,0}, {589,0}, {184,0}, {505,0}, {269,0},{8,0}, {83,0}};
	radix_sort(a, 10, 3);
	static_list_print(a);
}