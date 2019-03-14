#include <iostream>
using namespace std;

class base
{
public:
	base()
	{
		cout << "base()" << endl;
	};

	virtual ~base()
	{
		cout << "~base()" << endl;
	};
};

class drive : public base
{
public:
	drive()
	{
		cout << "drive()" << endl;
	};
	~drive()
	{
		cout << "~drive()" << endl;
	};
};

/*

			����˳��		����˳��(��������������)
base:         |						^
				V						 |
				 |						^
drive:		V						 |	

*/
int main_b_d()
{
	base *b = new drive();
	delete b;
	cout << "------------------" << endl;
	drive *d = new drive();
	delete d;

	system("pause");
	return 0;
}