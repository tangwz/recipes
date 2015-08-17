/*
 * Algorithm--InsertionSort：https://en.wikipedia.org/wiki/Insertion_sort
 * 
 */

/** 数组元素的类型 */
typedef int elem_t;
/**
* @brief 直接插入排序，时间复杂度 O(n^2).
*
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 无
*/
void straight_insertion_sort(elem_t a[], const int start, const int end)
{
	elem_t tmp;
	int i, j;

	for(i = start + 1; i < end; ++i){
		tmp = a[i];
		/* 与已排序的数逐一比较，大于tmp时，该数向后移 */
		for(j = i - 1; j >= start && a[j] > tmp; --j){
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
}

/**
* @brief 折半插入排序，时间复杂度 O(nlog2n).
*
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置
* @return 无
*/
void binary_insertion_sort(elem_t a[], const int start, const int end) 
{
	elem_t tmp;
	int i, j, left, right, mid;

	for(int i = start + 1; i < end; ++i){
		tmp = a[i];
		left =  start;
		right = i - 1;

		while(left <= right){
			mid = left + (right - left) / 2;
			if(tmp < a[mid]){
				right = mid - 1;
			}else{
				left = mid + 1;
			}
		}
		for(j = i - 1; j >= left; --j){
			a[j + 1] = a[j];
		}
		a[left] = tmp;
	}
}