#include <iostream>
#include <vector>
using namespace std;

//from https://www.kancloud.cn/digest/pieces-algorithm/163612


/*
快速排序
平均时间复杂度：O(nlogn)，最坏O(n^2)；
空间复杂度：O(logn)
*/
//递归实现
template<typename T>
void quickSort(vector<T> &v, int left, int right)
{
	if (left >= right) return;

	int i = left, j = right;
	T pivot = v[i];
	//cout << "piovt = " << pivot << endl;
	while (i < j)
	{
		while (i < j && v[j] >= pivot) --j;
		v[i] = v[j];
		while (i < j && v[i] <= pivot) ++i;
		v[j] = v[i];
	}
	v[i] = pivot;

	//for (auto i : v)
	//	cout << i << " ";
	//cout << endl;
	quickSort(v, left, i - 1);
	quickSort(v, i + 1, right);
}

int main_qs()
{
	vector<int> v = { 5, 6, 3, 2, 9, 1, 7, 10, 4 };
	//for (int i = 0; i < 10; ++i)
	//{
	//	int val = rand();
	//	v.push_back(val);
	//}
	for (auto i : v)
		cout << i << " ";
	cout << "\n-----------Sort begin--------------\n";

	quickSort(v, 0, v.size() - 1);

	cout << "\n-----------Sort end--------------\n";

	for (auto i : v)
		cout << i << " ";


	system("pause");
	return 0;
}