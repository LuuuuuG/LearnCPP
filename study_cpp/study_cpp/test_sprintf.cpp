#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main_test_sprintf()
{
	char s[256];
	memset(s, 0, 256);
	sprintf(s, "%s", "UNIX");
	cout << s << endl;
	
	strcat(s, " LINUX");
	cout << s << endl;
	system("pause");
	return 0;
}