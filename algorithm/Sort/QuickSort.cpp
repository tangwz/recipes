/*
 * Algorithm--QuickSort：https://en.wikipedia.org/wiki/Quicksort
 * 
 * Author:       Tangwz
 * Data:         2015/8/12
 * Blog:         tangwz.com
 */

/** 数组元素的类型 */
typedef int elem_t;
/*
* @brief 一趟划分.
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 基准元素的新位置
*/
int partition(elem_t a[], const int start, const int end) 
{
	int i = start;
	int j = end - 1;
	const elem_t pivot = a[i];
	while(i < j){
		while(i < j && a[j] >= pivot) j--;
		a[i] = a[j];
		while(i < j && a[i] <= pivot) i++;
		a[j] = a[i];
	}
	a[i] = pivot;
	return i;
}

/**
* @brief 快速排序.
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置
* @return 无
*/
void quick_sort(elem_t a[], const int start, const int end)
{
	if(start < end - 1){/* 至少两个元素 */
		const int pivot_pos = partition(a, start, end);
		quick_sort(a, start, pivot_pos);
		quick_sort(a, pivot_pos + 1, end);
	}
}