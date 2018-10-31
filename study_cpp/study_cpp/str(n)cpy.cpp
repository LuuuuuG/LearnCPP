#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>

using namespace std;
int main_strcpy()
{
	char info[1024];
	char info2[2];
	char* extinfo = "Hello";
	strcpy(info, extinfo);
	printf("strcpy: %s\n", info);

	strncpy(info2, extinfo, sizeof(extinfo));
	printf("strncpy: %s\n", info2);

	system("pause");
	return 0;
}