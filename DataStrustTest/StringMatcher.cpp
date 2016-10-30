#include "StringMatcher.h"
#include <assert.h>

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

// 根据模式串计算出前缀数组
KMPStrMatcher::KMPStrMatcher(const CPPString & p, CPPString & text):
	StringMatcher(text),pattern(p)
{
	
	patlen = p.length();
	assert(patlen > 0);

	prefix = new int[patlen];
	assert(prefix != 0);
	// 第一个字符时j肯定为0
	prefix[0] = 0;

	for (int i = 1; i < patlen; i++)
	{
		// 是否可以继续
		int k = prefix[i - 1];
		while (pattern[i] != pattern[k] && k != 0)
		{
			// 如果不能继续,则可以利用上个字符的最大前缀N,此时必定不会超过N了
			k = prefix[k - 1];
		}
		// 如果可以继续,则递加
		if (pattern[i] == pattern[k])
			prefix[i] = k + 1;
		else
			prefix[i] = 0;
	}
}

KMPStrMatcher::~KMPStrMatcher()
{
	delete []prefix;
}

int KMPStrMatcher::operator++()
{
	int end = text.length();
	int cur = pos + 1; // 正文游标, 只会递增
	int patp = 0; // 模式中的位置
	for (; cur < end; cur++)
	{
		while (patp > 0 && pattern[patp] != text[cur])
		{
			patp = prefix[patp - 1];
		}

		if (pattern[patp] == text[cur])
		{
			patp++;
			if (patp == patlen) 
			{
				// 发现匹配项
				pos = 1 + cur - patlen;
				return 1;
			}
		}
	}
	// 没有更多的匹配
	pos = -1;
	return 0;
}

BMStrMatcher::BMStrMatcher(const CPPString & pattern, CPPString & text)
	:StringMatcher(text),mPattern(pattern)
{
	patlen = mPattern.length();
	for (int i = 0; i < 256; i++)
	{
		mPosition[i] = 0;
	}
	for (int j = 0; mPattern[j]; j++)
	{
		// 如果模式中有相同的字符，以最后次出现的字符为准。
		mPosition[mPattern[j]] = j;
	}
}

int BMStrMatcher::operator++()
{
	pos += 1;
	int end = text.length() - patlen;
	int tmp = 0;
	while (pos <= end)
	{
		int j = patlen - 1;
		while (j >= 0 && text[pos + j] == mPattern[j])
			j--;
		if (j < 0) return 1; // 匹配成功
		// 步长最少增加1
		tmp = j - mPosition[text[pos + j]];
		if (tmp < 1) tmp = 1;
		pos += tmp;
	}
	pos = -1;
	return 0;
}

BMStrMatcher::~BMStrMatcher()
{
}
