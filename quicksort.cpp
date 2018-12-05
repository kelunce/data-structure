#include <iostream>
#include <stdio.h>

using namespace std;

int partition(int *v, int low, int high)
{
	int pivot = v[low];//作为划分标准的元素,之后v[low]可作为空位
	// 循环中的不变条件：在片段中,
	// 对所有小于low的i都有v[i] <= pivot
	// 对所有大于hight的i都有v[i]>= pivot
	while (low < high)
	{
		while (low < high && v[high] >= pivot) high--;
		// 经过上面while后，v[high] < piot, 下面把v[high]放到空位,之后v[high]变为空位
		if (low < high)
		{
			v[low] = v[high];
			low++;
		}
		while (low < high && v[low] <= pivot) low++;
		// 经过上面while后，v[low] > piot, 下面把v[low]放到空位v[high]，v[low]重新变为空位
		if (low < high)
		{
			v[high] = v[low];
			high--;
		}
	}
	//将pivot值放回两组之间
	v[high] = pivot;
    printf("low=%d hight=%d value=%d\n", low, high, pivot);
	return high;
}

void QuickSort(int *v, int low, int high)
{
	// 当分段中至多有一个元素时，什么不必做
	if (low >= high) return;
	// 对向量进行划分
	int mIdx = partition(v, low, high);
	QuickSort(v, low, mIdx - 1);
	QuickSort(v, mIdx + 1, high);
}

int BinarySearch(int *v, int low, int high, int value)
{
    if (low > high) return -1;
    if (low == high){
        if (value == v[low]) return low;
        return -1;
    }

    int mIdx = (low + high)/2;
    printf("mIdx=%d IdxValue=%d\n", mIdx, v[mIdx]);
    if (v[mIdx] == value) return mIdx;
    if (v[mIdx] < value) return BinarySearch(v, mIdx + 1, high, value);
    if (v[mIdx] > value) return BinarySearch(v, low, mIdx - 1, value);
}

int main()
{
    int a[100];
    int input = 0;
    int idx = 0;
    while (cin >> a[idx]) idx++;
    int size = idx - 1;
    int search_value = a[idx - 1];
    QuickSort(a, 0, size - 1);
    int i = 0;
    while(i < size){
        cout<< a[i++] << " ";
    }
    cout << endl;
    printf("search %d :%d\n", search_value, BinarySearch(a, 0, size - 1, search_value));
    return 1;
}
