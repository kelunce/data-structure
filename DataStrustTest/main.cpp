#include<iostream>
#include "CPPString.h"
using namespace std;

int main()
{
	CPPString a, b, c('a');
	a = "behind";
	cout << a << endl;
	b = a(1,4);
	cout << b << endl;
	a[0] = 'r';
	cout << a << endl;
	
    #ifdef _MSC_VER	
    system("pause");
    #else
    char y;
    cout<<"enter any key to exit";
    cin>>y;
    #endif

	return 0;
}

