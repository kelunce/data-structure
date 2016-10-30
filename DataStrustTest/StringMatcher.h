#pragma once
#include "CPPString.h"
/* 用法实例

SimpleStrMatcher aMatcher("er", "acceleromter");
for(aMatcher.init(); !aMatcher; aMatcher++)
{
	cout<<"found match at:"<<aMatcher.position()<<endl;
}
*/

// 所有模式匹配器基类
class StringMatcher
{
public:
	StringMatcher(CPPString &t);
	virtual int init();
	// 重载逻辑非运算符
	int operator !()const;
	// 子类的核心就是重载++,即怎么找到下一个匹配位置
	// 先自增再返回
	virtual int operator++();
	// 后置++参数必须有个int
	CPPSubString operator()();

	// 访问当前位置
	unsigned position() const;
	// 设置开始查找的位置
	void position(unsigned p);

	// 当前模式长度
	unsigned length();
	virtual ~StringMatcher();

protected:
	CPPString &text;
	int pos;
	unsigned patlen;
};

// 简单的字符串匹配, 复杂度O(mn)
class SimpleStrMatcher : public StringMatcher
{
public:
	SimpleStrMatcher(const CPPString &pat, CPPString &text);
	// 先自增再返回,寻找下一个匹配位置
	virtual int operator++();
private:
	const CPPString &pattern;
};

/*
  KMP算法,利用模式串(重复性)特征提高效率, 复杂度为O(m+n), n和m分别是正文字串和模式串的长度
  这是一种无回溯的字符串匹配算法(正文字符串的检查始终向前进展,即正文字符串中的每个字符只检查一次)
  适用于字符集小的文本匹配, 比如DNA片段搜索（DNA字符集只有4个）
 */
class KMPStrMatcher : public StringMatcher
{
public:
	// 根据模式串计算出前缀数组
	KMPStrMatcher(const CPPString &pattern, CPPString &text);
	~KMPStrMatcher();
	// 寻找下一个匹配位置
	virtual int operator++();
private:
	// 模式串
	const CPPString &pattern;
	// 前缀字符串数组
	int *prefix; 
	// 数组元素个数==pattern.length()
	// prefix[i] = j; 
	//表示在模式串里面的某个位置开始, 连续j个字符到第i个位置的一段内容与模式串最开始的j个字符完全相同
	// 对于i, 不存在更大的j满足上述关系
	// 比如模式串:  agctagcagctagctg
	// 对应前缀数组:0000123123456740
	// 前缀数组用于指示当字符匹配出现失败时应如何处理
	// 比如匹配到第11位时发现失败, 那么可以从模式串的第4个字符串往下比较
};

/* 每次模式串比较时，从右往左比较。如果发现不相等字符，则跳跃一次，跳跃步长规则：
	1. 如果不匹配的正文字符在模式串中存在，则根据mPosition数值作为步长跳跃。
	2. 如果不匹配的正文字符在模式串中不存在，则从正文当前字符的下一个字符开始重新匹配。
	3. 当模式串中的某字符在正文串中中出现多次，可能导致步长为负数！为避免这种往回走，限制步长大于0
	复杂度最优是O(n/m)，最差是O(mn)，平均是O(n)
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

/* 测试代码
void testSimpleStrMatcher()
{
CPPString text = "pattern match";
CPPString pat = "at";
//SimpleStrMatcher mat("at", text);// 临时构造的at字串会被释放!!
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
//SimpleStrMatcher mat("at", text);// 临时构造的at字串会被释放!!
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
//SimpleStrMatcher mat("at", text);// 临时构造的at字串会被释放!!
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