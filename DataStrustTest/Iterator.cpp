#include "Iterator.h"
#include "vector.h"


#include <iostream>
using namespace std;
void Test_VectorIterator()
{
	Vector<double> dblvec((unsigned)10, (double)2);
	VectorIterator<double> ditr(dblvec);
	double sum = 0;
	for (ditr.init(); !ditr; ++ditr)
	{
		cout << ditr() << '\n';
	}

	for (ditr.init(); !ditr; ++ditr)
	{
		sum += ditr();
	}
	cout << "sum=" << sum << endl;

	// set
	for (ditr.init(); !ditr; ++ditr)
	{
		ditr = ditr() + 3;
	}
	for (ditr.init(); !ditr; ++ditr)
	{
		cout << ditr() << '\n';
	}
}

void Test_EnumVectorIterator()
{
	enum colors
	{
		red,
		blue,
		yellow
	};
	enumVector <colors, double> hue(yellow);
	hue[red] = 0.52;
	hue[blue] = 0.27;
	hue[yellow] = 0.34;
	VectorIterator<double> citr(hue);
	for (citr.init(); !citr; ++citr)
	{
		cout << citr() << '\n';
	}
}

void Test_OrderedVectorIterator()
{
	orderedVector<double> dbvec;
	dbvec.add(1.2);
	dbvec.add(0.7);
	dbvec.add(0.1);
	dbvec.add(6.7);
	orderedVectorIterator<double> iter(dbvec);
	for (iter.init(); !iter; ++iter)
	{
		cout << iter() << '\n';
	}
}



