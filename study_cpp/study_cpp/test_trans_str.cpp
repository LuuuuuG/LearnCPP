#include <cstdint>
#include <cstdlib>
#include <iostream>

void test(char* c1, char* c2)
{
	printf("c1 = %s\n", c1);
	printf("c2 = %s\n", c2);
	}


int main_0822()
{
	char* c1 = "hello world";
	test(c1, "WTF");
	getchar();
	return 0;
}