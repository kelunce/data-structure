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

class SimpleStrMatcher : public StringMatcher
{
public:
	SimpleStrMatcher(const CPPString &pat, CPPString &text);
	// 先自增再返回
	virtual int operator++();
private:
	const CPPString &pattern;
};