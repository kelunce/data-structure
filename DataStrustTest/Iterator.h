#pragma once
#include "vector.h"

// 有纯虚函数的类，不能直接实例化
template < class  T>
class Iterator
{
public:
	// 对循环做初始化, 纯虚函数子类必须实现
	virtual int init() = 0;
	// 检查是否还有元素
	virtual int operator !() = 0;
	// 访问当前元素
	virtual T operator()() = 0;
	// 访问下一个元素
	virtual int operator++() = 0;
	// 改变当前元素
	virtual void operator=(T newValue) = 0;
};


/*
*  向量遍历器,实现遍历接口
*/
template<class T>
class VectorIterator :public  Iterator<T>
{
public:
	VectorIterator(Vector<T> &);

	VectorIterator(const VectorIterator &);

	// 实现遍历接口
	// 对循环做初始化
	virtual int init();
	// 检查是否还有元素
	virtual int operator !();
	// 访问当前元素
	virtual T operator()();
	// 访问下一个元素
	virtual int operator++();
	// 改变当前元素
	virtual void operator=(T newValue);

	// 向量遍历器自己的新操作
	int operator--();
	int key();
	Vector<T> &Data();

protected:
	// 数据成分
	unsigned currentKey;
	Vector<T> &data;
};

/*
	排序向量遍历器
*/
template <class T>
class orderedVectorIterator :public VectorIterator<T>
{
public:
	orderedVectorIterator(orderedVector<T> &x);
};


template<class T>
inline VectorIterator<T>::VectorIterator(Vector<T>& v) :data(v)
{
	// 建立和初始化向量遍历器
	init();
}

template<class T>
VectorIterator<T>::VectorIterator(const VectorIterator & x)
	:data(x.Data()), currentKey(x.key())
{
}

template<class T>
int VectorIterator<T>::init()
{
	currentKey = 0;
	return operator!();
}

template<class T>
int VectorIterator<T>::operator!()
{
	// 检查是否还有数据项
	return currentKey < data.length();
}

template<class T>
T VectorIterator<T>::operator()()
{
	// 返回当前项的值
	return data[currentKey];
}

template<class T>
int VectorIterator<T>::operator++()
{
	currentKey++;
	return  operator!();
}

template<class T>
void VectorIterator<T>::operator=(T newValue)
{
	data[currentKey] = newValue;
}

template<class T>
int VectorIterator<T>::operator--()
{
	if (currentKey > 0) currentKey--;
	return operator !();
}

template<class T>
int VectorIterator<T>::key()
{
	return currentKey;
}

template<class T>
Vector<T>& VectorIterator<T>::Data()
{
	return  data;
}

template<class T>
inline orderedVectorIterator<T>::orderedVectorIterator(orderedVector<T>& x) :
	VectorIterator<T>(x.data)
{

}

void Test_VectorIterator();
void Test_EnumVectorIterator();
void Test_OrderedVectorIterator();


