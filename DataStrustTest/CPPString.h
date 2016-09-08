#ifndef __CPPSTRING_H__
#define __CPPSTRING_H__

#include <iostream>

class CPPSubString;


class CPPString
{
public:
	// �������ַ���, ����ֻ��1�ֽ�
	CPPString();
	// ֧��CPPString a = 'a';
	CPPString(char);
	// ֧��CPPString a = "xxxx"
	CPPString(const char *);
	// ֧��ָ������������
	CPPString(unsigned);

	// ��������CPPString b = a;
	CPPString(const CPPString &);

	// �����Ӵ�����
	friend class CPPSubString;

	// ��ֵ�����, ��Ϊ��Ҫ�������ݳ�Ա, ����������Ϊ��Ա����ʵ��
	void operator =  (const CPPString &right);
	void operator += (const CPPString &right);

	// ȡ�Ӵ� ֧��CPPSubtring b = a(1,5);
	// ����������������������ͬ�ĵط��ǲ��������ɱ�!
	CPPSubString operator() (unsigned index, unsigned len);

	std::istream &getline(std::istream &);

	// ֧��ȡ��ʵ�ַ�����,������������
	unsigned length() const;

	int compare(const CPPString &)const;

	// ǿ��ת����C�ַ��� (char*)a
	// ���ض��������д��operator��!, �����������������ͬ
	// ���������������explicit,ǿ�����ǿ��ת������ֻ����ʽ����, ����Ĭ�ϵ���!!!
	// �������Ĭ�ϵ���, ��ô���ܽ���operator [] �ظ�, ��������õĶ�����!
	explicit operator char*() const;

	// ֧��a[1] = '2';
	// ������ô��������
	char & operator[](unsigned index)const;

	~CPPString();

private:
	unsigned buflen;
	char *buffer;
};

// ��׼�������, ����������
std::istream & operator>>(std::istream &in, CPPString &str);
std::ostream & operator<<(std::ostream &out, const CPPString &value);

// �Ƚ������, ����int
int operator<=(const CPPString &left, const CPPString &right);
int operator<(const CPPString &left, const CPPString &right);
int operator>=(const CPPString &left, const CPPString &right);
int operator>(const CPPString &left, const CPPString &right);
int operator==(const CPPString &left, const CPPString &right);
int operator!=(const CPPString &left, const CPPString &right);

// �ַ������
CPPString operator+(const CPPString &left, const CPPString &right);


/*
Ϊ��֧��
CPPString ind1 = "indicative";
CPPString ind2 = "induce";
ind1(3,3) = ind2(3,2);// ind1 will be "inductive"  TODO:�Ƿ��п������캯��������?
����1: ��ʼ�±�
����2: ����
*/
class CPPSubString
{
public:
	// ���캯�� 
	CPPSubString(CPPString &str, unsigned s, unsigned l);
	CPPSubString(CPPSubString &source);

	// �ַ���������Ը�ֵ���Ӵ�����
	void operator=(const CPPString &);
	// �Ӵ�����ǿ��ת��Ϊ�ַ�������
	operator CPPString()const;

	CPPString &GetBaseStr();
	const unsigned GetStartIdx();
	const unsigned GetLen();
private:
	// ����Ҫ���Ӵ���Ӧ���ִ����󻹻���
	CPPString &base;
	const unsigned start;
	const unsigned len;
};

#endif // !__CPPSTRING_H__



