/*
 * Algorithm--MergeSort：https://en.wikipedia.org/wiki/Merge_sort
 * 
 */

/** 数组元素的类型 */
typedef int elem_t;

/*
* @brief 将两个有序表合并成一个新的有序表
* @param[inout] a 待排序元素序列，包含两个有序表
* @param[in] tmp 与 a 等长的辅助数组
* @param[in] start a[start]~a[mid-1] 为第一个有序表
* @param[in] mid 分界点
* @param[in] end a[mid]~a[end-1] 为第二个有序表
* @return 无
*/
static void merge(elem_t a[], elem_t tmp[], const int start,
					const int mid, const int end)
{
	int i, j, k;
	for(i = 0; i < end; ++i)
		tmp[i] = a[i];

	/* i, j是检查指针，k是存放指针 */
	for(i = start, j = mid, k = start; i < mid && j < end; ++k){
		if(tmp[i] < tmp[j]){
			a[k] = tmp[i++];
		}else{
			a[k] = tmp[j++];
		}
	}
	/* 若第一个表未检测完，复制 */
	while (i < mid) a[k++] = tmp[i++];
	/* 若第二个表未检测完，复制 */
	while (j < end) a[k++] = tmp[j++];
}

/**
* @brief 归并排序.
* @param[inout] a 待排序元素序列
* @param[in] tmp 与 a 等长的辅助数组
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 无
* @note 无
* @remarks 无
*/
void merge_sort(elem_t a[], elem_t tmp[], const int start, const int end)
{
	if(start < end - 1){
		const int mid = (start + end) / 2;
		merge_sort(a, tmp, start, mid);
		merge_sort(a, tmp, mid, end);
		merge(a, tmp, start, mid, end);
	}
}