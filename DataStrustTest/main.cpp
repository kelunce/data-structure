#include<iostream>
#include "CPPString.h"
using namespace std;

void main()
{
	CPPString a, b, c('a');
	a = "behind";
	cout << a << endl;
	b = a(1,4);
	cout << b << endl;
	a[0] = 'r';
	cout << a << endl;
	system("pause");
	return;
}

