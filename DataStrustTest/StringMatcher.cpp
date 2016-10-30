#include "StringMatcher.h"
#include <assert.h>

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

// ����ģʽ�������ǰ׺����
KMPStrMatcher::KMPStrMatcher(const CPPString & p, CPPString & text):
	StringMatcher(text),pattern(p)
{
	
	patlen = p.length();
	assert(patlen > 0);

	prefix = new int[patlen];
	assert(prefix != 0);
	// ��һ���ַ�ʱj�϶�Ϊ0
	prefix[0] = 0;

	for (int i = 1; i < patlen; i++)
	{
		// �Ƿ���Լ���
		int k = prefix[i - 1];
		while (pattern[i] != pattern[k] && k != 0)
		{
			// ������ܼ���,����������ϸ��ַ������ǰ׺N,��ʱ�ض����ᳬ��N��
			k = prefix[k - 1];
		}
		// ������Լ���,��ݼ�
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
	int cur = pos + 1; // �����α�, ֻ�����
	int patp = 0; // ģʽ�е�λ��
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
				// ����ƥ����
				pos = 1 + cur - patlen;
				return 1;
			}
		}
	}
	// û�и����ƥ��
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
		// ���ģʽ������ͬ���ַ��������γ��ֵ��ַ�Ϊ׼��
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
		if (j < 0) return 1; // ƥ��ɹ�
		// ������������1
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
