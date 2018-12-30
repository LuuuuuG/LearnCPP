#include <iostream>
#include <cstdio>
using namespace std;


void replaceSpace(char *str, int length) {
	if (str == NULL)
		return;
	int CountOfBlanks = 0;
	int Originallength = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		Originallength++;
		if (str[i] == ' ')
			++CountOfBlanks;
	}
	int len = Originallength + 2 * CountOfBlanks;
	if (len + 1>length)
		return;

	char*pStr1 = str + Originallength;//¸´ÖÆ½áÊø·û¡®\0¡¯
	char*pStr2 = str + len;
	while (pStr1<pStr2)
	{
		if (*pStr1 == ' ')
		{
			*pStr2-- = '0';
			*pStr2-- = '2';
			*pStr2-- = '%';
		}
		else
		{
			*pStr2-- = *pStr1;
		}
		--pStr1;
	}
}

int main_str()
{

	char* str = "Hello world";
	replaceSpace(str, 256);

	cout << *str << endl;
	system("pause");
	return 0;
}