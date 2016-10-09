#include<iostream>
#include "CPPString.h"
#include "StringMatcher.h"
using namespace std;

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

void testSimpleStrMatcher()
{
	CPPString text = "pattern match";
	CPPString pat = "at";
	//SimpleStrMatcher mat("at", text);// 临时构造的at字串会被释放!!
	SimpleStrMatcher mat(pat, text);
	for (mat.init(); !mat; ++mat)
	{
		cout << "found match at:" << mat.position() << endl;
	}
}

void main()
{
	testSimpleStrMatcher();
	system("pause");
	return;
}

