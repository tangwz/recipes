/*
 * Algorithm--BubbleSort：https://en.wikipedia.org/wiki/Bubble_sort
 * 
 */

/** 数组元素的类型 */
typedef int elem_t;
/**
* @brief 冒泡排序.
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 无
* @note 无
* @remarks 无
*/
void bubble_sort(elem_t a[], const int start, const int end)
{
	int exchange;/* 是否发生交换 */
	elem_t tmp;
	int i, j;

	for(i = start; i < end - 1; ++i){
		exchange = 0;
		for(j = end - 1; j > i; --j){
			if(a[j - 1] > a[j]){
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
				exchange = 1;
			}
		}
		if(exchange == 0) return; /* 本趟无逆序，停止处理 */
	}
	
}