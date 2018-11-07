#include <iostream>
using namespace std;

class A
{
public:
	void FuncA()
	{
		printf("FuncA called\n");
	}
	virtual void FuncB()
	{
		printf("FuncB called\n");
	}
};

class B : public A
{
public:
	void FuncA()
	{
		A::FuncA();
		printf("FuncAB called\n");
	}
	virtual void FuncB()
	{
		printf("FuncBB called\n");
	}
};

int main_inheirt2()
{
	B b;
	A *pa;
	pa = &b;
	A *pa2 = new A;
	b.FuncA();		//FuncA called   FuncAB called
	b.FuncB();		//FuncBB called
	pa->FuncA();//FuncA called
	pa->FuncB();//FuncBB called
	pa2->FuncA();//FuncA called
	//delete pa2;

	system("pause");
	return 0;
}