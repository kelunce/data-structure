#pragma once
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