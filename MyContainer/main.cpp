#include "MyVector.h"
#include <iostream>

using namespace std;

int main()
{
	MyVector<int> vec = MyVector<int>(30);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	cout << "size: " << vec.size() << endl;
	cout << "capacity: " << vec.capacity() << endl;

	for (auto x : vec)
	{
		cout << x << endl;
	}

	vec.clear();
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.pop_back();

	cout << vec.front() << endl;
	cout << vec.back() << endl;
}