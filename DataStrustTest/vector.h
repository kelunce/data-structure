#pragma once
#include <assert.h>
/*
	����ģ���ࣺ����һ�����Ͳ���
	��ģ�����в����漰����������TԪ�صľ����������Ϊ�ڶ����ǻ���֪��T��ʲô���͡�
	����T����ʹ�����κ���Ҫд���͵ĵط�������Ϊ����ֵ��ָ�����͵ȡ�
	��������������
		1. �ڴ���Ԫ������˳��洢��һ���ڴ���еġ�
		2. ����ʹ���±���ٷ��ʡ������Ͼ������顣
		3. �����Ĵ�Сһ�㶼�ǹ̶��ġ�
		4. ������Ϊ��̬��������ʹ�á�������Ҫ�ƶ��ڴ浼�´���̫�󡣿��Կ���Ԥ������ơ�
*/
template <class T>
class Vector
{
public:
	// ���캯������Ҫָ����������
	Vector(unsigned numElements);
	Vector(unsigned numElements, T initValue);
	// �������캯��
	Vector(const Vector<T> &source);

	virtual ~Vector();

	// ͨ���±����Ԫ��, ��������
	T& operator[](unsigned index) const;
	// ��ֵ��������
	Vector<T> & operator=(const Vector<T> &source);

	unsigned length() const;

	// ��̬�ı�������С
	unsigned setSize(unsigned numOfElements);
	unsigned setSize(unsigned numOfElements, T initValue);
protected:
	// ʹ��ָ�뱣������
	T *data;
	unsigned size;
};

// ���Ժ���
void Test_Vector();

/*
	��������������ʹ��ָ����ʼ�±������. �������±��1990��ʼ,������0��
*/
template <class T>
class CBoundedVector : public Vector<T>
{
public:
	CBoundedVector(int low, int numOfElements);
	CBoundedVector(int low, int numOfElements, T& initValue);
	CBoundedVector(const CBoundedVector<T> & source);

	T& operator[](int index) const;

	// �����±�Ϸ�����
	int lowerBound() const;
	int upperBound() const;

protected:
	int lowbound;
};

void Test_BoundVector();


/*
   ö��������������ö�ٱ�����Ϊ�±������,�����֧�ִ�0��ʼ˳��ö�ٵı���
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
   ����������Ԫ������洢(�����С����)�����ҿ죬����������ʹ����ϷǼ̳�ʵ�֡�
*/

template<class T>
class orderedVector
{
public:
	// Ĭ�Ϲ���0��Ԫ������
	orderedVector();
	orderedVector(unsigned num);
	orderedVector(const orderedVector<T> & v);
	// Ϊ�˸�����ʹ�ñ���
	unsigned GetSize();
	// ǿ��ת��Ϊ��ͨ�������󡣷�������һ��ģ�������Ƿ�Ϸ���
	// �����������Ƿ�ͬһ���ڴ档
	operator Vector<T>()const;

	//  �пպ���
	int isEmpty() const;

	// ����������ֵ����Ԫ��
	void add(T value);
	// ��ɾ������ֵɾ��
	void remove(T value);
	void deleteAllValues();
	// ���ġ������±���ʣ��Ȳ鵽�ٸģ�
	T &operator[](unsigned index)const;

	// ���顿����ֵ���Ժ���
	int include(T value) const;
	// ���顿���ֲ���,�����������ҵ��˷����±꣬���򷵻�Ӧ�ò�����±ꡣ
	//  �Ƿ��ҵ���Ҫ��һ���жϣ��ο�include
	unsigned int binarySearch(T value);

	template<class T> friend class orderedVectorIterator;
private:
	Vector<T> data;
};



/*
	��������,��ı����������(��С����)
	ÿ��ѭ���跨��һ��Ԫ�ز��뵽�Ѿ�����Ĳ������еĺ���λ�ã�ʹ�õ���������Ȼ����
	���Ӷ�ΪO(n^2)�� �ȶ�����
*/
template<class T>
void InsertionSort(Vector<T> &vec);

/*
�ڲ�������Ĺ����У������ÿ�β���λ�õĴ����Ϊ��
���ö��ּ����ķ�����ǰ�������򲿷ֶ�λ��Ȼ���ƶ�����λ���Ժ��Ԫ�أ�������Ԫ�صĲ��롣
�۰����ֻ�Ǽ����˱Ƚϴ���������Ԫ�ص��ƶ��������䣬����ʱ�临�Ӷ�ΪO(n^2)���ȶ�����
*/

template<class T>
void BinaryInsertSort(Vector<T>& vec);

/*ϣ������
���ڰ���n��Ԫ�ص�����,��ȡ��һ������d1��n,��������ȫ��Ԫ�طֳ�d1���飬
���о���Ϊd1������Ԫ�ص���һ�顣�ڸ����ڽ�������Ȼ��ȡd2��d1�ظ������������������
ֱ��ȡdi��1��������Ԫ�ط���һ������Ϊֹ�������ڵ�������Բ���ֱ�Ӳ��뷨��
ʱ�临�Ӷ�ΪO(n^1.5)�����ȶ�����
*/
template<class T>
inline void ShellSort(Vector<T>& vec);


/************************************************************************/
/* ð������
/* ���һ�����в���˳��ģ���ôһ���ܹ��ҵ�����˳�򲻶Եģ�����ģ��������ݣ�������������
��λ�ý������������о͸��ӽ���һ��˳������С����ϵķ������򲢽��н��������վ���ʹ��������
��Ϊ����ġ�ʱ�临�Ӷ�ΪO(n^2)���ȶ�����
/************************************************************************/
template <class T>
void bubbleSort(Vector<T> &vec);

/************************************************************************/
/* ѡ������
/* �Ż�ð������������Ԫ�ش�������״̬ʱ���������н�����ʱ�ǲ���Ҫ�ģ���Ϊ�ں���Ĵ�����
������Ҫ���෴���ƶ������������Ϊ���ҵ����Ԫ�أ�ʵ���Ͽ��԰ѽ��������Ƴٵ�ȷ�������Ԫ��
֮���ٽ��С�������Ѱ�����Ԫ�ع����У�ֻҪ��ס�Ѿ����ֵ����Ԫ�ص�λ���±꼴����ÿ��ѭ����󽻻���
ʱ�临�Ӷ�ΪO(n^2)���ȶ�����
/************************************************************************/
template < class  T>
void SelectionSort(Vector<T> &vec);

/************************************************************************/
/* ��������
/* ����һ������������У����԰���һ����׼���������е�Ԫ�ط�Ϊ��С���࣬�ֱ����е����е�ǰ�κͺ�Ρ�
Ȼ���ٶԷֳ��������θ��Խ��л��֣���˽�����ȥ���ֳ��Ķ�Խ��Խ�̣������ֵõ�����С���ﶼ����ࣩ
ֻ��һ��Ԫ��ʱ��������ɡ�
ʱ�临�Ӷ�ΪO(nlgn)���n^2,���ȶ�����
/************************************************************************/
template<class T>
void QuickSort(Vector<T> &v);

void TestVectorSort();
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------ʵ�ֲ���---------------------------------------------------------
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
	// ������unsigned�������жϸ���
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
	// �������������������Ԫ��ֵΪ�趨����initValue
	if (numOfElements > oldSize)
	{
		for (i = oldSize; i < size; i++)
		{
			data[i] = initValue;
		}
	}
	return size;
}


// ���������ʾ���ø���ָ�������Ĺ��캯������ֹ�����Զ����ɵĸ����޲ι���
// ���ұ����ڳ�ʼ���б��У�
template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements) :
	lowbound(low), Vector<T>(numOfElements)
{
	// ����ʱ�����ȹ��츸������
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements, T & initValue) :
	lowbound(low), Vector<T>(numOfElements, initValue)
{
	// ����ʱ�����ȹ��츸������
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(const CBoundedVector<T>& source) :
	lowbound(source.lowerBound()), Vector<T>(source)
{
	// ����ʱ�����ȹ��츸������
}

template<class T>
inline T & CBoundedVector<T>::operator[](int index) const
{
	// ���ø��ຯ��������������
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


// ���������ʾ���ø���ָ�������Ĺ��캯������ֹ�����Զ����ɵĸ����޲ι���
// ���ұ����ڳ�ʼ���б��У�
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
	// ������캯��Ĭ�ϻ����vector��һ��unsinged�����Ĺ��캯��������ʼ��data
	// ���ܲ���data��ʼ���������п�ʱsize��û�г�ʼ����Σ�ա�
}

template<class T>
orderedVector<T>::orderedVector(unsigned num) :data(num)
{
	// ������캯��Ĭ�ϻ����vector��һ��unsinged�����Ĺ��캯��������ʼ��data
}

template<class T>
inline orderedVector<T>::orderedVector(const orderedVector<T>& v)
{
	// ������԰�vǿ��ת��Ϊvector����ôֱ�Ӹ���
	data = (Vector<T>)v;
	// �������ѭ��copy
}

template<class T>
unsigned orderedVector<T>::GetSize()
{
	return data.length();
}

// TODO: ��������һ��ģ�壬�Ƿ�Ϸ���
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

	// index�±�����Ԫ��Ǩ��һλ�����������
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
		// TODO:������Թ۲�forѭ������length�Ƿ񱻼����Ρ�
		// �����LPC����mapping����ô��copy��һ��mapping�ģ�����������Ƿ�������
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
	// �տ����䡣
	unsigned low = 0;
	unsigned high = data.length();
	while (low < high)
	{
		unsigned mid = (low + high) / 2;
		if (data[mid] == value) return mid;
		else if (data[mid] < value) low = mid + 1;
		else high = mid;
	}
	// ���low�Ѿ���high���ˣ�˵��������Ҫ�����index��
	return low;
}

/*
��������ΰѱ�����Ԫ�ز��뵽����λ�ã�������õķ����ǣ�
���Ȱ�Ҫ����ĵ�ǰԪ�ط���һ����ʱ�����У��ڳ�һ����λ��
���Ǵ��ڿ�λǰ���Ԫ�أ�������Ԫ�رȵ�ǰԪ�أ��Ͱ����Ƶ���λ���������Ϊ�ǿ�λ��ǰ�ƶ��ˡ���
ֱ�����ֿ�λǰ���Ԫ�ز��ȵ�ǰԪ�ش�ʱ������顣�ѵ�ǰ��Ԫ�ط��������еĿ�λ�
*/
template<class T>
inline void InsertionSort(Vector<T>& vec)
{
	int n = vec.length(), j, next;
	// ��ǰҪ�����Ԫ�ػ���
	T temp;
	// �ӵڶ���Ԫ�ؿ�ʼ��
	for (next = 1; next < n; next++)
	{
		// ʼ�ձ���vec[0..next-1]�������
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
	// ��ǰҪ�����Ԫ�ػ���
	T temp;
	for (next = 1; next < n; next++)
	{
		temp = vec[next];

		// ���ַ�����
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


//Shell����(ϣ������)
/*
ԭʼ����:
49 38 65 97 26 13 27 49 55 4

������5
49             13              --->��һ������
13             49              --->��һ������������
   38             27
   27             38
      65             49
      49             65
         97             55
         55             97
            26             4   --->����������
            4              26  --->����������������
13 27 49 55 4  49 38 65 97 26  --->���

������2
13    49    4     38    97     --->��һ������
4     13    38    49    97     --->��һ������������
   27    55    49    65    26  --->�ڶ�������
   26    27    49    55    65  --->�ڶ�������������
4  26 13 27 38 49 49 55 97 65  --->���

������1
4  26 13 27 38 49 49 55 97 65  --->��һ������
4  13 26 27 38 49 49 55 65 97  --->��һ������������

������0������

*/
template<class T>
inline void ShellSort(Vector<T>& vec)
{
	int gap, i, j;
	T temp;
	int n = vec.length();
	// ���ǲ���d1=n/2, d2=d1/2....
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
	//����������λ��i��j��Ԫ��
	T temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}

template <class T>
void bubbleSort(Vector<T> &vec)
{
	// ������Ԫ�ذ���������
	int top, i;
	for (top = vec.length() - 1; top > 0; top--)
	{
		// �ҳ�0~top��Χ�ڵ����Ԫ�أ��ŵ�vec[top]
		for (int i = 0; i < top; i++)
		{
			//vec[i] ����0~i֮������Ԫ��
			if (vec[i + 1] < vec[i])
			{
				swap(vec, i + 1, i);
				// vec[i + 1] ��0~i + 1��Χ�����Ԫ��
			}
		}
		// vec[top..lenght -1] һ���Ѿ�����
	}
}

template < class  T>
void SelectionSort(Vector<T> &vec)
{
	// ������Ԫ�ذ�����������
	int largest, top, j;
	for (top = vec.length() - 1; top > 0; top--)
	{
		// ȷ�����Ԫ�ص��±�
		for (largest = 0, j = 1; j <= top; j++)
		{
			//����vec[largest]��0~j-1һ�ε����Ԫ��
			if (vec[largest] < vec[j])
				largest = j;
			//vec[largest]��0~jһ�������Ԫ��
		}
		if (top != largest)
			swap(vec, top, largest);
		// vec[top..length-1]�Ѿ��ź�����
	}
}


template<class T>
int partition(Vector<T> &v, int low, int high)
{
	T pivot = v[low];//��Ϊ���ֱ�׼��Ԫ��,֮��v[low]����Ϊ��λ
	// ѭ���еĲ�����������Ƭ����,
	// ������С��low��i����v[i] <= pivot
	// �����д���hight��i����v[i]>= pivot
	while (low < high)
	{
		while (low < high && v[high] >= pivot) high--;
		// ��������while��v[high] < piot, �����v[high]�ŵ���λ,֮��v[high]��Ϊ��λ
		if (low < high)
		{
			v[low] = v[high];
			low++;
		}
		while (low < high && v[low] <= pivot) low++;
		// ��������while��v[low] > piot, �����v[low]�ŵ���λv[high]��v[low]���±�Ϊ��λ
		if (low < high)
		{
			v[high] = v[low];
			high--;
		}
	}
	//��pivotֵ�Ż�����֮��
	v[high] = pivot;
	return high;
}

template<class T>
void QuickSort(Vector<T> &v, int low, int high)
{
	// ���ֶ���������һ��Ԫ��ʱ��ʲô������
	if (low >= high) return;
	// ���������л���
	int mIdx = partition(v, low, high);
	QuickSort(v, low, mIdx - 1);
	QuickSort(v, mIdx + 1, high);
}

// ���ط�ʽ����
template<class T>
void QuickSort(Vector<T> &v)
{
	QuickSort(v, 0, v.length() - 1);
}
