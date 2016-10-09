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
  �������ַ���С���ı�ƥ��
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