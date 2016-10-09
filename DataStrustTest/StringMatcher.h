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

class SimpleStrMatcher : public StringMatcher
{
public:
	SimpleStrMatcher(const CPPString &pat, CPPString &text);
	// �������ٷ���
	virtual int operator++();
private:
	const CPPString &pattern;
};