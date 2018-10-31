#include <cstdio>
#include <iostream>

int main_self_add()
{
	int i = 1;
	printf("%d %d\n", ++i, ++i);	//3 3
	printf("%d %d\n", ++i, i++);	//4 3
	printf("%d %d\n", i++, i++);	//5 5
	printf("%d %d\n", i++, ++i);	//8 8 
	printf("i = %d\n", i);	//9

	printf("-------------------------\n");
	i = 1;
	printf("%d %d\n", i++, ++i);	//2 2
	printf("%d %d\n", i++, i++);	//3 3
	printf("%d %d\n", ++i, i++);	//6 5
	printf("%d %d\n", ++i, ++i);	//9 9
	printf("i = %d\n", i);	//9

	system("pause");
	return 0;
}