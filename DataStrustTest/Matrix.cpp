#include "Matrix.h"

template<class T>
Matrix<T>::Matrix(unsigned numberOfRows, unsigned numberOfColumns):rows(numberOfRows)
{
	// 为矩阵的各个行分配存储空间
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		rows[i] = new Vector<T>(numberOfColumns);
		assert(rows[i] != 0);
	}
}

template<class T>
Matrix<T>::Matrix(unsigned numberOfRows, unsigned numberOfColumns, T initValue) :rows(numberOfRows)
{
	// 为矩阵的各个行分配存储空间
	for (unsigned i = 0; i < numberOfRows; i++)
	{
		rows[i] = new Vector<T>(numberOfColumns, initValue);
		assert(rows[i] != 0);
	}
}

template<class T>
Matrix<T>::~Matrix()
{
	unsigned max = rows.length(), i;
	Vector<T> *p;
	for (i = 0; i < max; i++)
	{
		p = rows[i];
		rows[i] = 0;
		delete p;
	}
}

template<class T>
Vector<T>& Matrix<T>::operator[](unsigned index) const
{
	return *rows[index];
}

template<class T>
int Matrix<T>::numberRows() const
{
	return rows.length();
}

template<class T>
int Matrix<T>::numberColumns() const
{
	return rows[0]->length();
}

template<class T>
inline Matrix<T> operator*(const Matrix<T>& left, const Matrix<T>& right)
{
	int n = left.numberRows(),
		m = left.numberColumns(),
		p = right.numberColumns();
	int i, j, k;
	assert(m == right.numberRows());

	Matrix<T> ret(n, p);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p; j++)
		{
			for (k = 0; k < m; k++)
				ret[i][j] += left[i][k] * right[k][j];
		}
	}
	return ret;
}