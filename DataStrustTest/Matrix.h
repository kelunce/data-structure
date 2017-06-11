#pragma once
#include "vector.h"

template <class T>
class Matrix
{
public:
	Matrix(unsigned numberOfRows, unsigned numberOfColumns);
	Matrix(unsigned numberOfRows, unsigned numberOfColumns, T initValue);
	~Matrix();

	Vector<T> &operator [](unsigned index) const;
	int numberRows() const;
	int numberColumns() const;

private:
	// Vector<T> 二维数组
	Vector<Vector<T> *> rows;
};

// 外部模板函数形式
template < class T>
Matrix<T> operator *(const Matrix<T> & left, const Matrix<T> & right);


