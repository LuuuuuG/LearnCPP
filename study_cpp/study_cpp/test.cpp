#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int get_max_diff(vector<int> list)
{
	if (list.empty())
		return 0;
	if (list.size() == 1)
		return list[0];
	int max_dif = list[1] - list[0];
	int min_ele = list[0];
	for (int i = 1; i < list.size(); ++i)
	{
		max_dif = max(max_dif, list[i] - min_ele);
		min_ele = min(min_ele, list[i]);
	}
	return max_dif;
}

void testChar()
{
	for (char i = 0; i < 256; ++i)
	{
		printf("%d\n", i);//����ѭ��
	}
}

int main_test() {

	vector<int> v1 = { 1, 2, 3, 4, 5 };
	vector<int> v2 = { 5, 4, 3, 2, 1 };
	int res = get_max_diff(v1);
	//cout << res << endl;

	//cout << "====================" << endl;
	//int a = 2, b = 3;
	//res = abs(a - b);
	//cout << res << endl;

	cout << "==========" << endl;
	int a[5] = { 1,2,3,4,5 };
	int* ptr = (int*)(&a + 1);
	printf("%d\n", *ptr);
	printf("%d %d\n", *(a + 1), *(ptr - 1));

	system("pause");
	return 0;
}
