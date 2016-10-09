#include "StringMatcher.h"

StringMatcher::StringMatcher(CPPString &t):text(t),pos(0)
{
}

int StringMatcher::init()
{
	pos = -1;
	// note这样调用本对象的自增是否正确?
	return operator++();
}

int StringMatcher::operator!() const
{
	// 返回pos是否在界限之内(即找到了)
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
		//  note因为子串可以转换为字串, 故可以这样写
		if (pattern == text(pos, patlen))
			return 1;
	}
	pos = -1;
	return 0;
}

