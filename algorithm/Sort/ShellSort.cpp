/*
 * Algorithm--ShellSort：https://en.wikipedia.org/wiki/Shellsort
 * 
 * Author:       Tangwz
 * Data:         2015/8/12
 * Blog:         tangwz.com
 */

/** 数组元素的类型 */
typedef int elem_t;
/*
* @brief 一趟希尔插入排序.
**
和一趟直接插入排序相比，仅有一点不同，就是前后元素的间距是 gap 而不是 1
*
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @param[in] gap 间隔
* @return 无
*/
static void shell_insert(elem_t a[], const int start, const int end, const int gap) 
{
	elem_t tmp;
	int i, j;

	for(i = start + gap; i < end; ++i){
		tmp = a[i];
		for(j = i - gap; tmp < a[j] && j >= start; j-= gap){
			a[j + gap] = a[j];
		}
		a[j + gap] = tmp;
	}
}

/*
* @brief 希尔排序.
* @param[inout] a 待排序元素序列
* @param[in] start 开始位置
* @param[in] end 结束位置，最后一个元素后一个位置，即左闭右开区间
* @return 无
*/
void shell_sort(elem_t a[], const int start, const int end)
{
	int gap = end - start;
	while(gap > 1){
		gap = gap / 3 + 1;
		shell_insert(a, start, end, gap);
	}
}