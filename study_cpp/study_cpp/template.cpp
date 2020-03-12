#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct A
{
	int a;
	double b;
	char c;
};

struct Link
{
	int a;
	double b;
	char c;
};

template<class T1, class T2>
void copy2Link(const vector<T1>& v1, vector<T2>& v2)
{
	if (sizeof(T1) != sizeof(T2)) return;
	v2.resize(v1.size());
	for (auto it = 0; it != v1.size(); ++it)
		memcpy(&v2[it], &v1[it], sizeof(v1[it]));
}


int main_temp()
{
	A a;
	a.a = 10;
	a.b = 20.22;
	a.c = 'A';

	vector<A> vecA;
	for (int i = 0; i < 5; ++i)
		vecA.push_back(a);

	vector<Link> vecLink;
	copy2Link(vecA, vecLink);
	//std::swap_ranges(vecA.begin(), vecA.end(), vecLink.begin());

	system("pause");
	return 0;
}