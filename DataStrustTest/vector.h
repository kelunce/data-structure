#pragma once
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