#include <iostream>
using namespace std;

union
{
	int iArea;
	struct
	{
		int iCity : 20;//位域，占用20位  不到3字节
		int iCountry : 10;
		int iReserved : 2;
	}Area_st;
}Area_un;

struct IPAREA_UN
{
	union
	{
		int iArea;
		struct
		{
			int iCity : 20;
			int iCountry : 10;
			int iReserved : 2;
		}Area_st;
	}Area_un;
};

struct IPAREA
{
	int iArea;
	int iCity : 20;
	int iCountry : 10;
	int iReserved : 2;
};

struct s3
{
	int i;
	int j;
	int a;
	double b;
};

struct s4
{
	int i : 8;
	int j : 4;
	int a : 3;
	double b;
};


struct BF1
{
	char f1 : 3;
	char f2 : 4;
	char f3 : 5;
};

int main_sizeof()
{
	cout << " sizeof(Area_un): " << sizeof(Area_un) << endl;//4
	cout << " sizeof(IPAREA_UN): " << sizeof(IPAREA_UN) << endl;//4
	cout << " sizeof(IPAREA): " << sizeof(IPAREA) << endl;//8

	cout << " sizeof(s3): " << sizeof(s3) << endl;//24
	cout << " sizeof(s4): " << sizeof(s4) << endl;//16

	cout << " sizeof(BF1): " << sizeof(BF1) << endl;//2

	system("pause");
	return 0;
}