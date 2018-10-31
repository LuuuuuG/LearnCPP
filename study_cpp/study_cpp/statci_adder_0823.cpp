#include <iostream>
using namespace std;


int test()
{
	static int val = 0;
	return val++;
}

int main_0823()
{
	for (int i = 0; i < 5; ++i)
	{
		int res = test();
		cout << res << endl;
	}
	system("pause");
	return 0;
}