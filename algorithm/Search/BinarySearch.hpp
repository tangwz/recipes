/*
 * Algorithm--BinarySearch：https://en.wikipedia.org/wiki/Binary_search_algorithm
 * 
 */

/** 数组元素的类型 */
typedef int elem_t;
/**
* @brief 有序顺序表的折半查找算法.
*
* @param[in] a 存放数据元素的数组，已排好序
* @param[in] n 数组的元素个数
* @param[in] x 要查找的元素
* @return 如果找到 x，则返回其下标。 如果找
* 不到 x 且 x 小于 array 中的一个或多个元素，则为一个负数，该负数是大
* 于 x 的第一个元素的索引的按位求补。 如果找不到 x 且 x 大于 array 中的
* 任何元素，则为一个负数，该负数是（最后一个元素的索引加 1）的按位求补。
*/
int binary_search(const elem_t a[], const int n, const elem_t x)
{
	int left = 0, right = n - 1, mid;
	while(left <= right){
		mid = left + (mid - left) / 2;
		if(x > a[mid]){
			left = mid + 1;
		}else if(x < a[mid]){
			right = mid - 1;
		}else{
			return mid;
		}
	}
	return -(left + 1);
}