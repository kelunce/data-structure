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
	//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
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
	//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
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
	//SimpleStrMatcher mat("at", text);// ��ʱ�����at�ִ��ᱻ�ͷ�!!
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

