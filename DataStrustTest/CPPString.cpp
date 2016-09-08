#include "CPPString.h"
#include <assert.h>

// 建立空字符串, 长度只有1字节
CPPString::CPPString()
{
	buflen = 1;
	buffer = new char[buflen];
	assert(buffer != 0);
	buffer[buflen - 1] = '\0';
}

// 支持CPPString a = 'a';
CPPString::CPPString(char c)
{
	buflen = 2;
	buffer = new char[buflen];
	assert(buffer != 0);
	buffer[0] = c;
	buffer[buflen - 1] = '\0';
}

// 返回字符串中真实字符个数, 不包含末尾结束符
unsigned cstrLen(const char * text)
{
	int len = 0;
	if (text == 0) return len;
	for (;; ++len)
	{
		if (text[len] == '\0')
			break;
	}
	return len ;
}

// 支持CPPString a = "xxxx"
CPPString::CPPString(const char * inittext)
{
	buflen = 1 + cstrLen(inittext);
	buffer = new char[buflen];
	assert(buffer != 0 );
	
	for (unsigned i = 0; inittext[i] != '\0'; ++i)
	{
		buffer[i] = inittext[i];
	}
	buffer[buflen - 1] = '\0';
}

// 支持指定缓冲区长度
CPPString::CPPString(unsigned size)
{
	assert(size >= 0);
	buflen = 1 + size;
	buffer = new char[buflen];
	assert(buffer != 0);

	for (unsigned i = 0; i < buflen; ++i)
	{
		buffer[i] = '\0';
	}

}

unsigned CPPString::length() const
{
	return cstrLen(buffer);
}

// 支持a[1] = '2';
char nothing;
char & CPPString::operator[](unsigned index) const
{
	if (index >= cstrLen(buffer))
	{
		nothing = '\0';
		return nothing;
	}
	return buffer[index];
}

int CPPString::compare(const CPPString &val) const
{
	char *p = buffer;
	const char *q = (const char*)val;
	for (; (*p != '\0') && (*p = *q); p++, q++);
	return *p - *q;
}

// 强制转换到C字符串 (char*)a
CPPString::operator char*() const
{
	return buffer;
}


// 拷贝函数CPPString b = a;
CPPString::CPPString(const CPPString & initstr)
{
	buflen = 1 + cstrLen((const char *)initstr);
	buffer = new char[buflen];
	assert(buffer != 0);
	unsigned i = 0;
	while(initstr[i] != '\0')
	{
		buffer[i++] = initstr[i];
	}
	buffer[i] = '\0';
}

void CPPString::operator=(const CPPString & right)
{
	const unsigned rightLength = right.length();
	// 如果字符串容量不够则需要申请
	if (rightLength >= buflen)
	{
		delete[] buffer;
		buflen = 1 + rightLength;
		buffer = new char[buflen];
		assert(buffer != 0);
	}

	// 实际复制
	unsigned i = 0;
	for (; i < rightLength; ++i )
	{
		buffer[i] = right[i];
	}
	buffer[i] = '\0';
}

void CPPString::operator+=(const CPPString & right)
{
	unsigned i;
	unsigned conlen = length() + right.length();
	if (conlen >= buflen)
	{
		char* newbuf = new char[1 + conlen];
		assert(newbuf != 0);
		for (i = 0; buffer[i] != '\0'; i++)
		{
			newbuf[i] = buffer[i];
		}
		delete[] buffer;
		buflen = 1 + conlen;
		buffer = newbuf;
	}
	else
	{
		i = cstrLen(buffer);
	}

	for (unsigned j = 0; right[j] != '\0'; j++, i++)
	{
		buffer[i] = right[j];
	}
	buffer[i] = '\0';
}

CPPSubString CPPString::operator()(unsigned index, unsigned len)
{
	if (index >= length())
	{
		index = 0;
		len = 0;
	}
	int maxLen = length() - index;
	len = len > maxLen ? maxLen : len;
	// 把自己传递给子串对象
	CPPString &base = *this;
    return CPPSubString(base, index, len);
}

std::istream & CPPString::getline(std::istream &in)
{
	in.getline(buffer, buflen, '\n');
	return in;
}

CPPString::~CPPString()
{
	delete[] buffer;
	buffer = 0;
}

std::istream & operator>>(std::istream & in, CPPString & str)
{
	char inbuffer[1000];
	if (in >> inbuffer)
	{
		str = inbuffer;
	}
	else
		str = "";
	return in;
}

std::ostream & operator<<(std::ostream & out, const CPPString & value)
{
	out << (const char*)value << std::endl;
	return out;
}

int operator<=(const CPPString & left, const CPPString & right)
{
	return left.compare(right) <= 0;
}

int operator<(const CPPString & left, const CPPString & right)
{
	return left.compare(right) < 0;
}

int operator>=(const CPPString & left, const CPPString & right)
{
	return left.compare(right) >= 0;;
}

int operator>(const CPPString & left, const CPPString & right)
{
	return left.compare(right) > 0;
}

int operator==(const CPPString & left, const CPPString & right)
{
	return left.compare(right) == 0;
}

int operator!=(const CPPString & left, const CPPString & right)
{
	return left.compare(right) != 0;
}

CPPString operator+(const CPPString & left, const CPPString & right)
{
	CPPString result(left);
	result += right;
	return result;
}

CPPSubString::CPPSubString(CPPString & str, unsigned s, unsigned l)
	:base(str),start(s),len(l)
{
	// 使用初始化列表
}

CPPSubString::CPPSubString(CPPSubString & source)
	:base(source.GetBaseStr()),start(source.GetStartIdx()),len(source.GetLen())
{
	// 使用初始化列表
}

void CPPSubString::operator=(const CPPString &rstr)
{
	unsigned i;
	if (len == rstr.length())
	{
		for (i = 0; i < len; i++)
		{
			base[start + i] = rstr[i];
		}
		return;
	}

	unsigned newLen = rstr.length() + base.length() - len;
	char *newdata = new char[newLen + 1];
	assert(newdata != 0);

	for (i = 0; i < start; i++)
	{
		newdata[i] = base[i];
	}

	for (unsigned j = 0; j < rstr.length(); j++)
	{
		newdata[i++] = rstr[j];
	}

	for (unsigned j = start + len; base[j] != '\0'; j++)
	{
		newdata[i++] = base[j];
	}
	newdata[i] = '\0';
	assert(i == newLen + 1);

	delete[] base.buffer;
	base.buffer = newdata;
	base.buflen = newLen + 1;
	return;
}

CPPSubString::operator CPPString() const
{
	char *buf = new char[len + 1];
	assert(buf != 0);

	for (unsigned i = 0; i < len; i++)
	{
		buf[i] = base[start + i];
	}
	buf[len] = '\0';

	CPPString result(buf);
	delete[]buf;
	return result;
}

CPPString & CPPSubString::GetBaseStr()
{
	return base;
}

const unsigned CPPSubString::GetStartIdx()
{
	return start;
}

const unsigned CPPSubString::GetLen()
{
	return len;
}
