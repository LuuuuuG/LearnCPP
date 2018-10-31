#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main_memset()
{
	char str[10] = "Hello";
	//strcpy_s(str, "");
	memset(str, 0, sizeof(str));
	cout << "str = " << str << endl;

	system("pause");
	return 0;
}