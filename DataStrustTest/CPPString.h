#ifndef __CPPSTRING_H__
#define __CPPSTRING_H__

#include <iostream>

class CPPSubString;


class CPPString
{
public:
	// 建立空字符串, 长度只有1字节
	CPPString();
	// 支持CPPString a = 'a';
	CPPString(char);
	// 支持CPPString a = "xxxx"
	CPPString(const char *);
	// 支持指定缓冲区长度
	CPPString(unsigned);

	// 拷贝函数CPPString b = a;
	CPPString(const CPPString &);

	// 允许子串访问
	friend class CPPSubString;

	// 赋值类操作, 因为需要访问数据成员, 所以这里作为成员函数实现
	void operator =  (const CPPString &right);
	void operator += (const CPPString &right);

	// 取子串 支持CPPSubtring b = a(1,5);
	// 括号运算符和其他运算符不同的地方是参数个数可变!
	CPPSubString operator() (unsigned index, unsigned len);

	std::istream &getline(std::istream &);

	// 支持取真实字符长度,不包含结束符
	unsigned length() const;

	int compare(const CPPString &)const;

	// 强制转换到C字符串 (char*)a
	// 返回对象的类型写在operator后!, 这个和其他操作符不同
	// 而且这里必须声明explicit,强调这个强制转换函数只能显式调用, 不能默认调用!!!
	// 如果可以默认调用, 那么功能将和operator [] 重复, 而引起调用的二意性!
	// C++11开始explicit才可以修饰非构造函数
	explicit operator char*() const;

	// 支持a[1] = '2';
	// 留意怎么返回引用
	char & operator[](unsigned index)const;

	~CPPString();

private:
	unsigned buflen;
	char *buffer;
};

// 标准输入输出, 返回流对象
std::istream & operator>>(std::istream &in, CPPString &str);
std::ostream & operator<<(std::ostream &out, const CPPString &value);

// 比较运算符, 返回int
int operator<=(const CPPString &left, const CPPString &right);
int operator<(const CPPString &left, const CPPString &right);
int operator>=(const CPPString &left, const CPPString &right);
int operator>(const CPPString &left, const CPPString &right);
int operator==(const CPPString &left, const CPPString &right);
int operator!=(const CPPString &left, const CPPString &right);

// 字符串相加
CPPString operator+(const CPPString &left, const CPPString &right);


/*
为了支持
CPPString ind1 = "indicative";
CPPString ind2 = "induce";
ind1(3,3) = ind2(3,2);// ind1 will be "inductive"  TODO:是否有拷贝构造函数被调用?
参数1: 起始下标
参数2: 长度
*/
class CPPSubString
{
public:
	// 构造函数 
	CPPSubString(CPPString &str, unsigned s, unsigned l);
	CPPSubString(CPPSubString &source);

	// 字符串对象可以赋值给子串对象
	void operator=(const CPPString &);
	// 子串对象强制转换为字符串对象
	operator CPPString()const;

	CPPString &GetBaseStr();
	const unsigned GetStartIdx();
	const unsigned GetLen();
private:
	// 这里要求子串对应的字串对象还活着
	CPPString &base;
	const unsigned start;
	const unsigned len;
};



/*  测试代码
void testCppstring()
{
CPPString a, b, c('a');
a = "behind";
cout << a << endl;
b = a(1, 4);
cout << b << endl;
a[0] = 'r';
cout << a << endl;
}


*/
#endif // !__CPPSTRING_H__




