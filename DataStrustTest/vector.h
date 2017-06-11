#pragma once
#include <assert.h>
/*
	向量模板类：增加一个类型参数
	在模板类中不能涉及到对于类型T元素的具体操作。因为在定义是还不知道T是什么类型。
	类型T可以使用在任何需要写类型的地方。如作为返回值，指针类型等。
	向量类型特征：
		1. 内存中元素们是顺序存储在一个内存块中的。
		2. 可以使用下标快速访问。本质上就是数组。
		3. 向量的大小一般都是固定的。
		4. 可以作为动态长度数组使用。但是需要移动内存导致代价太大。可以考虑预分配机制。
*/
template <class T>
class Vector
{
public:
	// 构造函数都需要指定向量容量
	Vector(unsigned numElements);
	Vector(unsigned numElements, T initValue);
	// 拷贝构造函数
	Vector(const Vector<T> &source);

	virtual ~Vector();

	// 通过下标访问元素, 返回引用
	T& operator[](unsigned index) const;
	// 赋值操作符。
	Vector<T> & operator=(const Vector<T> &source);

	unsigned length() const;

	// 动态改变向量大小
	unsigned setSize(unsigned numOfElements);
	unsigned setSize(unsigned numOfElements, T initValue);
protected:
	// 使用指针保存数组
	T *data;
	unsigned size;
};

// 测试函数
void Test_Vector();

/*
	定界向量：可以使用指定开始下标的向量. 比如让下标从1990开始,而不是0。
*/
template <class T>
class CBoundedVector : public Vector<T>
{
public:
	CBoundedVector(int low, int numOfElements);
	CBoundedVector(int low, int numOfElements, T& initValue);
	CBoundedVector(const CBoundedVector<T> & source);

	T& operator[](int index) const;

	// 返回下标合法界限
	int lowerBound() const;
	int upperBound() const;

protected:
	int lowbound;
};

void Test_BoundVector();


/*
   枚举向量：可以用枚举变量作为下标的数组,这里仅支持从0开始顺序枚举的变量
*/

template <class E, class T>
class enumVector:public Vector<T>
{
public:
	enumVector(E max);
	enumVector(const enumVector &v);

	T& operator[](E index);
};

void Test_EnumVector();

/*
   排序向量：元素有序存储(假设从小到大)，查找快，但插入慢。使用组合非继承实现。
*/

template<class T>
class orderedVector
{
public:
	// 默认构成0个元素数组
	orderedVector();
	orderedVector(unsigned num);
	orderedVector(const orderedVector<T> & v);
	// 为了更方便使用本类
	unsigned GetSize();
	// 强制转化为普通向量对象。返回另外一个模板类型是否合法？
	// 这两个对象是否同一个内存。
	operator Vector<T>()const;

	//  判空函数
	int isEmpty() const;

	// 【增】根据值插入元素
	void add(T value);
	// 【删】根据值删除
	void remove(T value);
	void deleteAllValues();
	// 【改】根据下标访问（先查到再改）
	T &operator[](unsigned index)const;

	// 【查】根据值测试函数
	int include(T value) const;
	// 【查】二分查找,这个函数如果找到了返回下标，否则返回应该插入的下标。
	//  是否找到需要进一步判断，参考include
	unsigned int binarySearch(T value);

	template<class T> friend class orderedVectorIterator;
private:
	Vector<T> data;
};



/*
	插入排序,会改变待排序向量(从小到大)
	每次循环设法把一个元素插入到已经排序的部分序列的合适位置，使得到的序列仍然有序
	复杂度为O(n^2)， 稳定排序
*/
template<class T>
void InsertionSort(Vector<T> &vec);

/*
在插入排序的过程中，如果把每次插入位置的处理改为：
先用二分检索的方法对前面已排序部分定位，然后移动插入位置以后的元素，最后完成元素的插入。
折半查找只是减少了比较次数，但是元素的移动次数不变，所以时间复杂度为O(n^2)，稳定排序
*/

template<class T>
void BinaryInsertSort(Vector<T>& vec);

/*希尔排序
对于包含n个元素的向量,先取定一个整数d1＜n,把向量的全部元素分成d1个组，
所有距离为d1倍数的元素当做一组。在各组内进行排序；然后取d2＜d1重复上述分组和排序工作。
直到取di＝1，即所有元素放在一个组中为止。各组内的排序可以采用直接插入法。
时间复杂度为O(n^1.5)，不稳定排序
*/
template<class T>
inline void ShellSort(Vector<T>& vec);


/************************************************************************/
/* 冒泡排序
/* 如果一个序列不是顺序的，那么一定能够找到两个顺序不对的（逆序的）相邻数据，把这两个数据
的位置交换，整个序列就更接近于一个顺序的序列。不断的发现逆序并进行交换，最终就能使整个序列
成为有序的。时间复杂度为O(n^2)，稳定排序
/************************************************************************/
template <class T>
void bubbleSort(Vector<T> &vec);

/************************************************************************/
/* 选择排序
/* 优化冒泡排序：在两个元素处于逆序状态时，立即进行交换有时是不必要的，因为在后面的处理中
可能又要做相反的移动。如果仅仅是为了找到最大元素，实际上可以把交换动作推迟到确定了最大元素
之后再进行。这样在寻找最大元素过程中，只要记住已经发现的最大元素的位置下标即可在每次循环最后交换。
时间复杂度为O(n^2)，稳定排序
/************************************************************************/
template < class  T>
void SelectionSort(Vector<T> &vec);

/************************************************************************/
/* 快速排序
/* 对于一个被排序的序列，可以按照一个标准，把序列中的元素分为大小两类，分别排列到序列的前段和后段。
然后再对分出的两个段各自进行划分，如此进行下去，分出的段越来越短，当最后分得的所有小段里都（最多）
只有一个元素时，排序完成。
时间复杂度为O(nlgn)，最坏n^2,不稳定排序
/************************************************************************/
template<class T>
void QuickSort(Vector<T> &v);

void TestVectorSort();
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------实现部分---------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

template<class T>
Vector<T>::Vector(unsigned numElements) :size(numElements)
{
	data = new T[size];
	assert(data != 0);
}

template<class T>
Vector<T>::Vector(unsigned numElements, T initValue) :size(numElements)
{
	data = new T[size];
	assert(data != 0);

	for (int i = 0; i < size; i++)
	{
		data[i] = initValue;
	}
}

template<class T>
Vector<T>::Vector(const Vector<T>& source) :size(source.length())
{
	data = new T[size];
	assert(data != 0);

	for (int i = 0; i < size; i++)
	{
		data[i] = source[i];
	}
}

template<class T>
Vector<T>::~Vector()
{
	delete[] data;
	data = 0;
	size = 0;
}

template<class T>
T & Vector<T>::operator[](unsigned index) const
{
	// 这里是unsigned，无需判断负数
	assert(index < size);
	return data[index];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& source)
{
	if (size != source.length())
	{
		// new buffer
		T *np = new T[source.length()];
		assert(np != 0);
		// free old buffer
		delete[] data;
		// save new buffer
		size = source.length();
		data = np;
	}
	// copy data
	for (int i = 0; i < size; i++)
	{
		data[i] = source[i];
	}
	return *this;
}

template<class T>
unsigned Vector<T>::length() const
{
	return size;
}

template<class T>
unsigned Vector<T>::setSize(unsigned numOfElements)
{
	if (size != numOfElements)
	{
		// new buffer
		T *np = new T[numOfElements];
		assert(np != 0);

		// copy old data, how much?
		int n = numOfElements > size ? size : numOfElements;
		for (int i = 0; i < n; i++)
		{
			np[i] = data[i];
		}

		// free old buffer
		delete[] data;
		// save new buffer
		size = numOfElements;
		data = np;
	}
	return size;
}

template<class T>
unsigned Vector<T>::setSize(unsigned numOfElements, T initValue)
{
	int oldSize = size;
	setSize(numOfElements);
	// 如果是增长，则增长的元素值为设定参数initValue
	if (numOfElements > oldSize)
	{
		for (i = oldSize; i < size; i++)
		{
			data[i] = initValue;
		}
	}
	return size;
}


// 这里必须显示调用父类指定参数的构造函数，防止调用自动生成的父类无参构造
// 而且必须在初始化列表中！
template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements) :
	lowbound(low), Vector<T>(numOfElements)
{
	// 构造时必须先构造父类数据
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements, T & initValue) :
	lowbound(low), Vector<T>(numOfElements, initValue)
{
	// 构造时必须先构造父类数据
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(const CBoundedVector<T>& source) :
	lowbound(source.lowerBound()), Vector<T>(source)
{
	// 构造时必须先构造父类数据
}

template<class T>
inline T & CBoundedVector<T>::operator[](int index) const
{
	// 调用父类函数，操作符函数
	return Vector<T>::operator[](index - lowbound);
}

template<class T>
inline int CBoundedVector<T>::lowerBound() const
{
	return lowbound;
}

template<class T>
inline int CBoundedVector<T>::upperBound() const
{
	return lowbound + Vector<T>::length() - 1;
}


// 这里必须显示调用父类指定参数的构造函数，防止调用自动生成的父类无参构造
// 而且必须在初始化列表中！
template<class E, class T>
inline enumVector<E, T>::enumVector(E max) :Vector<T>(1 + int(max))
{

}

template<class E, class T>
inline enumVector<E, T>::enumVector(const enumVector & v)
{
	::Vector<T>(v);
}

template<class E, class T>
inline T & enumVector<E, T>::operator[](E index)
{
	return Vector<T>::operator[](int(index));
}


template<class T>
inline orderedVector<T>::orderedVector() :data(0)
{
	// 这个构造函数默认会调用vector的一个unsinged参数的构造函数！来初始化data
	// 不能不对data初始化，否则判空时size都没有初始化！危险。
}

template<class T>
orderedVector<T>::orderedVector(unsigned num) :data(num)
{
	// 这个构造函数默认会调用vector的一个unsinged参数的构造函数！来初始化data
}

template<class T>
inline orderedVector<T>::orderedVector(const orderedVector<T>& v)
{
	// 如果可以把v强制转换为vector，那么直接复制
	data = (Vector<T>)v;
	// 否则可以循环copy
}

template<class T>
unsigned orderedVector<T>::GetSize()
{
	return data.length();
}

// TODO: 返回另外一个模板，是否合法？
template<class T>
orderedVector<T>::operator Vector<T>() const
{
	return data;
}

template<class T>
inline int orderedVector<T>::isEmpty() const
{
	return data.length() == 0;
}

template<class T>
inline void orderedVector<T>::add(T value)
{
	unsigned max = data.length();
	unsigned index = binarySearch(value);
	data.setSize(max + 1);

	// index下标后面的元素迁移一位，这就是消耗
	for (unsigned I = max; I > index; I--)
	{
		data[I] = data[I - 1];
	}
	data[index] = value;
}

template<class T>
inline void orderedVector<T>::remove(T value)
{
	unsigned index = binarySearch(value);
	if (index < data.length() && (value == data[index]))
	{
		// TODO:这里可以观察for循环变量length是否被计算多次。
		// 如果是LPC遍历mapping，那么会copy出一份mapping的！【这件事情是否调查过】
		for (unsigned I = index; I < (data.length() - 1); I++)
		{
			data[I] = data[I - 1];
		}
	}
}

template<class T>
inline void orderedVector<T>::deleteAllValues()
{
	data.setSize(0);
}

template<class T>
inline T & orderedVector<T>::operator[](unsigned index) const
{
	return data[index];
}

template<class T>
inline int orderedVector<T>::include(T value) const
{
	unsigned index = binarySearch(value);
	if (index < data.length() && (value == data[index]))
		return 1;
	return 0;
}

template<class T>
inline unsigned int orderedVector<T>::binarySearch(T value)
{
	// 闭开区间。
	unsigned low = 0;
	unsigned high = data.length();
	while (low < high)
	{
		unsigned mid = (low + high) / 2;
		if (data[mid] == value) return mid;
		else if (data[mid] < value) low = mid + 1;
		else high = mid;
	}
	// 这个low已经比high大了，说明就是需要插入的index了
	return low;
}

/*
问题是如何把被处理元素插入到合适位置，这里采用的方法是：
首先把要插入的当前元素放在一个临时变量中，腾出一个空位。
考虑处在空位前面的元素，如果这个元素比当前元素，就把它移到空位里。（可以认为是空位向前移动了。）
直到发现空位前面的元素不比当前元素大时结束检查。把当前的元素放入向量中的空位里。
*/
template<class T>
inline void InsertionSort(Vector<T>& vec)
{
	int n = vec.length(), j, next;
	// 当前要插入的元素缓存
	T temp;
	// 从第二个元素开始排
	for (next = 1; next < n; next++)
	{
		// 始终保持vec[0..next-1]是有序的
		temp = vec[next];
		for (j = next - 1; j > 0 && temp < vec[j]; j--)
		{
			vec[j + 1] = vec[j];
			vec[j] = temp;
		}
	}
}


template<class T>
inline void BinaryInsertSort(Vector<T>& vec)
{
	int n = vec.length(), j, next, low, high, mid;
	// 当前要插入的元素缓存
	T temp;
	for (next = 1; next < n; next++)
	{
		temp = vec[next];

		// 二分法检索
		low = 0;
		high = next - 1;
		while (low <= high) {
			mid = (low + high) / 2; 
			if (temp < vec[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}

		for (j = next - 1; j > high; --j)
			vec[j + 1] = vec[j];

		vec[high + 1] = temp;
	}
}


//Shell排序(希尔排序)
/*
原始数据:
49 38 65 97 26 13 27 49 55 4

步长：5
49             13              --->第一组数据
13             49              --->第一组数据排序结果
   38             27
   27             38
      65             49
      49             65
         97             55
         55             97
            26             4   --->第五组数据
            4              26  --->第五组数据排序结果
13 27 49 55 4  49 38 65 97 26  --->结果

步长：2
13    49    4     38    97     --->第一组数据
4     13    38    49    97     --->第一组数据排序结果
   27    55    49    65    26  --->第二组数据
   26    27    49    55    65  --->第二组数据排序结果
4  26 13 27 38 49 49 55 97 65  --->结果

步长：1
4  26 13 27 38 49 49 55 97 65  --->第一组数据
4  13 26 27 38 49 49 55 65 97  --->第一组数据排序结果

步长：0，结束

*/
template<class T>
inline void ShellSort(Vector<T>& vec)
{
	int gap, i, j;
	T temp;
	int n = vec.length();
	// 这是步长d1=n/2, d2=d1/2....
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < n; i++)
		{
			for (j = i - gap; j >= 0 && vec[j] > vec[j + gap]; j -= gap)
			{
				temp = vec[j];
				vec[j] = vec[j + gap];
				vec[j + gap] = temp;
			}
		}
	}
}

template <class T>
void swap(Vector<T> &vec, int i, int j)
{
	//交换向量中位置i和j的元素
	T temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}

template <class T>
void bubbleSort(Vector<T> &vec)
{
	// 将向量元素按升序排序
	int top, i;
	for (top = vec.length() - 1; top > 0; top--)
	{
		// 找出0~top范围内的最大元素，放到vec[top]
		for (int i = 0; i < top; i++)
		{
			//vec[i] 总是0~i之间的最大元素
			if (vec[i + 1] < vec[i])
			{
				swap(vec, i + 1, i);
				// vec[i + 1] 是0~i + 1范围的最大元素
			}
		}
		// vec[top..lenght -1] 一段已经排序
	}
}

template < class  T>
void SelectionSort(Vector<T> &vec)
{
	// 将向量元素按照升序排序
	int largest, top, j;
	for (top = vec.length() - 1; top > 0; top--)
	{
		// 确定最大元素的下标
		for (largest = 0, j = 1; j <= top; j++)
		{
			//保持vec[largest]是0~j-1一段的最大元素
			if (vec[largest] < vec[j])
				largest = j;
			//vec[largest]是0~j一段中最大元素
		}
		if (top != largest)
			swap(vec, top, largest);
		// vec[top..length-1]已经排好序了
	}
}


template<class T>
int partition(Vector<T> &v, int low, int high)
{
	T pivot = v[low];//作为划分标准的元素,之后v[low]可作为空位
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
	return high;
}

template<class T>
void QuickSort(Vector<T> &v, int low, int high)
{
	// 当分段中至多有一个元素时，什么不必做
	if (low >= high) return;
	// 对向量进行划分
	int mIdx = partition(v, low, high);
	QuickSort(v, low, mIdx - 1);
	QuickSort(v, mIdx + 1, high);
}

// 重载方式定义
template<class T>
void QuickSort(Vector<T> &v)
{
	QuickSort(v, 0, v.length() - 1);
}
