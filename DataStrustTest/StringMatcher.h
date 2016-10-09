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
  适用于字符集小的文本匹配
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