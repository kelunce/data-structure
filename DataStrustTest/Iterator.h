#pragma once
#include "vector.h"

// �д��麯�����࣬����ֱ��ʵ����
template < class  T>
class Iterator
{
public:
	// ��ѭ������ʼ��, ���麯���������ʵ��
	virtual int init() = 0;
	// ����Ƿ���Ԫ��
	virtual int operator !() = 0;
	// ���ʵ�ǰԪ��
	virtual T operator()() = 0;
	// ������һ��Ԫ��
	virtual int operator++() = 0;
	// �ı䵱ǰԪ��
	virtual void operator=(T newValue) = 0;
};


/*
*  ����������,ʵ�ֱ����ӿ�
*/
template<class T>
class VectorIterator :public  Iterator<T>
{
public:
	VectorIterator(Vector<T> &);

	VectorIterator(const VectorIterator &);

	// ʵ�ֱ����ӿ�
	// ��ѭ������ʼ��
	virtual int init();
	// ����Ƿ���Ԫ��
	virtual int operator !();
	// ���ʵ�ǰԪ��
	virtual T operator()();
	// ������һ��Ԫ��
	virtual int operator++();
	// �ı䵱ǰԪ��
	virtual void operator=(T newValue);

	// �����������Լ����²���
	int operator--();
	int key();
	Vector<T> &Data();

protected:
	// ���ݳɷ�
	unsigned currentKey;
	Vector<T> &data;
};

/*
	��������������
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
	// �����ͳ�ʼ������������
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
	// ����Ƿ���������
	return currentKey < data.length();
}

template<class T>
T VectorIterator<T>::operator()()
{
	// ���ص�ǰ���ֵ
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


