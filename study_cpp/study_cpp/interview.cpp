#include <iostream>
using namespace std;


int main_intvie(void)
{
	char cA;
	unsigned char ucB;
	unsigned short usC;

	cA = 128;
	ucB = 128;

	usC = cA + ucB;
	printf("1: 0X%x\n", usC);//1

	usC = cA + (short)ucB;
	printf("2: 0X%x\n", usC);//2

	usC = (unsigned char)cA + ucB;
	printf("3: 0X%x\n", usC);//3 
	usC = cA + (char)ucB;
	printf("4: 0X%x\n", usC);//4 
	getchar();

	return EXIT_SUCCESS;
}