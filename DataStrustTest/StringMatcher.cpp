#include "StringMatcher.h"

StringMatcher::StringMatcher(CPPString &t):text(t),pos(0)
{
}

int StringMatcher::init()
{
	pos = -1;
	// note�������ñ�����������Ƿ���ȷ?
	return operator++();
}

int StringMatcher::operator!() const
{
	// ����pos�Ƿ��ڽ���֮��(���ҵ���)
	return (pos >= 0) && (pos < text.length());
}

int StringMatcher::operator++()
{
	return 0;
}


CPPSubString StringMatcher::operator()()
{
	return text(position(),length());
}

unsigned StringMatcher::position() const
{
	return pos;
}

void StringMatcher::position(unsigned p)
{
	pos = p;
	operator ++();
}


unsigned StringMatcher::length()
{
	return patlen;
}

StringMatcher::~StringMatcher()
{
	//nothing
}

SimpleStrMatcher::SimpleStrMatcher(const CPPString & pat, CPPString & text):
	StringMatcher(text),pattern(pat)
{
	patlen = pat.length();
}

int SimpleStrMatcher::operator++()
{
	int last = text.length() - patlen;
	for (pos++; pos <= last; pos++)
	{
		//  note��Ϊ�Ӵ�����ת��Ϊ�ִ�, �ʿ�������д
		if (pattern == text(pos, patlen))
			return 1;
	}
	pos = -1;
	return 0;
}

