#include <iostream>
using namespace std;

int addNumByBit(int a, int b)
{
	int sum, carry;
	while (b)
	{
		sum = a ^ b;
		carry = (a & b) << 1;
		a = sum;
		b = carry;
	}
	return a;
}

int main_add_no_plus()
{
	int a = 3;
	int b = 4;
	int res = addNumByBit(a, b);

	cout << " a + b = " << res << endl;
	system("pause");
	return 0;
}