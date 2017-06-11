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
	// Vector<T> ��ά����
	Vector<Vector<T> *> rows;
};

// �ⲿģ�庯����ʽ
template < class T>
Matrix<T> operator *(const Matrix<T> & left, const Matrix<T> & right);


