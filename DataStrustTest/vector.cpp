#include "vector.h"
#include "CPPString.h"
#include "Iterator.h"
#include <iostream>
using namespace std;

static void wordLengthFreq(Vector<int> &counts)
{
	const int lengthmax = counts.length();
	int len;
	CPPString word;
	while (std::cin >> word)
	{
		len = word.length();
		if (len < lengthmax)
			counts[len]++;
		else
			counts[0]++;

		for (int i = 0; i < counts.length(); i++)
		{
			std::cout << counts[i] << ", ";
		}
		std::cout << std::endl;
	}
}

void Test_Vector()
{
	Vector<int> vTest(6, 0);
	wordLengthFreq(vTest);
	
}

#include <ctype.h>
void letterOccurs(CBoundedVector<int> &counts, const CPPString & text)
{
	// 统计字符串text中字母次数
	assert(counts.lowerBound() == 'a');
	assert(counts.upperBound() == 'z');

	for (int i = 0; text[i] != '\0'; i++)
	{
		char c = text[i];
		if (isupper(c)) c = tolower(c);
		if (islower(c)) counts[c]++;
	}

}
void Test_BoundVector()
{
	int initValue = 0;
	CBoundedVector<int> counts('a', 26, initValue);
	CPPString word;
	while (std::cin >> word)
	{
		letterOccurs(counts, word);
		// printf
		for (char c = 'a'; c <= 'z'; c++)
		{
			std::cout << "letter "<< c << " occurrences " << counts[c] << " times \n";


		}
	}
}

enum colors {red, orange, yellow, green, blue};
void Test_EnumVector()
{
	enumVector<colors, double> data(blue);
	data[blue] = 1.414;
	data[red] = 1.732;
	data[green] = data[blue] + 1.02;
	std::cout << "red: " << data[red] <<
		" orange: " << data[orange] <<
		" yellow: " << data[yellow] <<
		" green : " << data[green] <<
		" blue :" << data[blue] << "\n";
}

#include <time.h>  
void TestVectorSort()
{
	int size = 10;
	Vector<double> dbvec(size);

	srand((unsigned)time(NULL));
	for (int i = 0; i < size; ++i)
	{
		dbvec[i] = rand()%100;
	}

	//BinaryInsertSort(dbvec);
	//InsertionSort(dbvec);
	//ShellSort(dbvec);
	//QuickSort(dbvec);
	SelectionSort(dbvec);

	VectorIterator<double> iter(dbvec);
	for (iter.init(); !iter; ++iter)
	{
		cout << iter() << '\n';
	}
}