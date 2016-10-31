#include "vector.h"
#include <assert.h>


template<class T> 
Vector<T>::Vector(unsigned numElements):size(numElements)
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
Vector<T>::Vector(const Vector<T>& source):size(source.length())
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



template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements):
	lowbound(low), Vector<T>(numOfElements)
{
	// 构造时必须先构造父类数据
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(int low, int numOfElements, T & initValue):
	lowbound(low), Vector<T>(numOfElements, initValue)
{
	// 构造时必须先构造父类数据
}

template<class T>
inline CBoundedVector<T>::CBoundedVector(const CBoundedVector<T>& source):
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













#include "CPPString.h"
#include <iostream>

static void wordLengthFreq(Vector<int> &counts)
{
	const int lengthmax = counts.length();
	int len;
	CPPString word;
	while (std::cin >> word)
	{
		len = word.length();
		if (len < lengthmax)
			counts[len]++;
		else
			counts[0]++;

		for (int i = 0; i < counts.length(); i++)
		{
			std::cout << counts[i] << ", ";
		}
		std::cout << std::endl;
	}
}

void Test_Vector()
{
	Vector<int> vTest(6, 0);
	wordLengthFreq(vTest);
	
}

#include <ctype.h>
void letterOccurs(CBoundedVector<int> &counts, const CPPString & text)
{
	// 统计字符串text中字母次数
	assert(counts.lowerBound() == 'a');
	assert(counts.upperBound() == 'z');

	for (int i = 0; text[i] != '\0'; i++)
	{
		char c = text[i];
		if (isupper(c)) c = tolower(c);
		if (islower(c)) counts[c]++;
	}

}
void Test_BoundVector()
{
	int initValue = 0;
	CBoundedVector<int> counts('a', 26, initValue);
	CPPString word;
	while (std::cin >> word)
	{
		letterOccurs(counts, word);
		// printf
		for (char c = 'a'; c <= 'z'; c++)
		{
			std::cout << "letter "<< c << " occurrences " << counts[c] << " times \n";
		}
	}
}
