#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main_for_each()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; ++i)
		v1.push_back(i);
	for_each(v1.begin(), v1.end(), [](int i){ cout << i << " "; });
	//for_each(v2.begin(), v2.end(), [v2](int i) { v2.push_back(i + 10); });
	system("pause");
	return 0;
}