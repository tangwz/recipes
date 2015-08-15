/*
 * Algorithm--SelectionSort：https://en.wikipedia.org/wiki/Selection_sort
 * 
 * Author:       Tangwz
 * Data:         2015/8/14
 * Blog:         tangwz.com
 */

/** 数组元素的类型 */
typedef int elem_t;
/**
* @brief 简单选择排序.
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 无
*/
void selection_sort(elem_t a[], int start, int end)
{
	elem_t tmp;
	int i, j, k;

	for(i = start; i < end; ++i){
		k = i;
		/* 在a[i]到a[end - 1]中寻找最小元素 */
		for(j = i + 1; j < end; ++j)
			if(a[j] < a[k]) k = j;
		/* 交换 */
		if(k != i){
			tmp = a[i];
			a[i] = a[k];
			a[k] = tmp;
		}
	}
}