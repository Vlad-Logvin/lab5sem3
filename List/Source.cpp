#include <iostream>
#include "List.h"

using namespace std;


int main()
{
	List<char> list;
	list.push_back('a');
	list.push_back('b');
	list.push_back('c');

	List<char> list2;
	list2 = list;

	for (auto a : list2)
	{
		cout << a << endl;
	}

	cout << endl << endl << (list2 == list) << endl << endl;

	list2.push_back('d');

	cout << endl << endl << (list2 == list) << endl << endl;

	list2 << cout;

	return 0;
}
