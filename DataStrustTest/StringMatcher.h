#pragma once
#include "CPPString.h"
/* �÷�ʵ��

SimpleStrMatcher aMatcher("er", "acceleromter");
for(aMatcher.init(); !aMatcher; aMatcher++)
{
	cout<<"found match at:"<<aMatcher.position()<<endl;
}
*/

// ����ģʽƥ��������
class StringMatcher
{
public:
	StringMatcher(CPPString &t);
	virtual int init();
	// �����߼��������
	int operator !()const;
	// ����ĺ��ľ�������++,����ô�ҵ���һ��ƥ��λ��
	// �������ٷ���
	virtual int operator++();
	// ����++���������и�int
	CPPSubString operator()();

	// ���ʵ�ǰλ��
	unsigned position() const;
	// ���ÿ�ʼ���ҵ�λ��
	void position(unsigned p);

	// ��ǰģʽ����
	unsigned length();
	virtual ~StringMatcher();

protected:
	CPPString &text;
	int pos;
	unsigned patlen;
};

// �򵥵��ַ���ƥ��, ���Ӷ�O(mn)
class SimpleStrMatcher : public StringMatcher
{
public:
	SimpleStrMatcher(const CPPString &pat, CPPString &text);
	// �������ٷ���,Ѱ����һ��ƥ��λ��
	virtual int operator++();
private:
	const CPPString &pattern;
};

/*
  KMP�㷨,����ģʽ��(�ظ���)�������Ч��, ���Ӷ�ΪO(m+n), n��m�ֱ��������ִ���ģʽ���ĳ���
  ����һ���޻��ݵ��ַ���ƥ���㷨(�����ַ����ļ��ʼ����ǰ��չ,�������ַ����е�ÿ���ַ�ֻ���һ��)
  �������ַ���С���ı�ƥ��, ����DNAƬ��������DNA�ַ���ֻ��4����
 */
class KMPStrMatcher : public StringMatcher
{
public:
	// ����ģʽ�������ǰ׺����
	KMPStrMatcher(const CPPString &pattern, CPPString &text);
	~KMPStrMatcher();
	// Ѱ����һ��ƥ��λ��
	virtual int operator++();
private:
	// ģʽ��
	const CPPString &pattern;
	// ǰ׺�ַ�������
	int *prefix; 
	// ����Ԫ�ظ���==pattern.length()
	// prefix[i] = j; 
	//��ʾ��ģʽ�������ĳ��λ�ÿ�ʼ, ����j���ַ�����i��λ�õ�һ��������ģʽ���ʼ��j���ַ���ȫ��ͬ
	// ����i, �����ڸ����j����������ϵ
	// ����ģʽ��:  agctagcagctagctg
	// ��Ӧǰ׺����:0000123123456740
	// ǰ׺��������ָʾ���ַ�ƥ�����ʧ��ʱӦ��δ���
	// ����ƥ�䵽��11λʱ����ʧ��, ��ô���Դ�ģʽ���ĵ�4���ַ������±Ƚ�
};

/* ÿ��ģʽ���Ƚ�ʱ����������Ƚϡ�������ֲ�����ַ�������Ծһ�Σ���Ծ��������
	1. �����ƥ��������ַ���ģʽ���д��ڣ������mPosition��ֵ��Ϊ������Ծ��
	2. �����ƥ��������ַ���ģʽ���в����ڣ�������ĵ�ǰ�ַ�����һ���ַ���ʼ����ƥ�䡣
	3. ��ģʽ���е�ĳ�ַ������Ĵ����г��ֶ�Σ����ܵ��²���Ϊ������Ϊ�������������ߣ����Ʋ�������0
	���Ӷ�������O(n/m)�������O(mn)��ƽ����O(n)
*/
class BMStrMatcher : public StringMatcher
{
public:
	BMStrMatcher(const CPPString &pattern, CPPString & text);
	virtual int operator ++();
	~BMStrMatcher ();

private:
	const CPPString &mPattern;
	short int mPosition[256];
};

/* ���Դ���
void testSimpleStrMatcher()
{
CPPString text = "pattern match";
CPPString pat = "at";
//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
SimpleStrMatcher mat(pat, text);
for (mat.init(); !mat; ++mat)
{
cout << __func__ << " found match at:" << mat.position() << endl;
}
}

void testKMPStrMatcher()
{
CPPString text = "pattern match";
CPPString pat = "at";
//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
KMPStrMatcher mat(pat, text);
for (mat.init(); !mat; ++mat)
{
cout << __func__ << " found match at:" << mat.position() << endl;
}
}

void testBMStrMatcher()
{
CPPString text = "pattern match";
CPPString pat = "at";
//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
BMStrMatcher mat(pat, text);
for (mat.init(); !mat; ++mat)
{
cout << __func__ << " found match at:" << mat.position() << endl;
}
}

void main()
{
testSimpleStrMatcher();
testKMPStrMatcher();
testBMStrMatcher();
system("pause");
return;
}


*/