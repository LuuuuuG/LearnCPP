#include <stdio.h>
int getSize(int data[]) {
	return sizeof(data);
}
struct MyStruct
{

};

int main_sizeof() {
	int data1[5] = { 1,2,3,4,5 };
	int size1 = sizeof(data1);//20

	int* data2 = data1;
	int size2 = sizeof(data2);//8

	int size3 = getSize(data1);//8

	printf("%d, %d, %d", size1, size2, size3);

	int size4 = sizeof(int);//4

	int size5 = sizeof(void*);//8

	char sz[100];
	int size6 = sizeof(sz);//100

	MyStruct stru;

	printf("stru = %d\n", sizeof(stru)); //1

	getchar();
	return 0;
}