#include <iostream>
using namespace std;

class A
{
private:
	char data;
public:
	A(){ data = 'A'; }
	virtual void Show(){ printf("A\n"); };
	virtual void DispA(){ printf("a\n"); };
};

class B : public A
{
private:
	int data;
public:
	B(){ data = 'B'; }
	virtual void Show(){ printf("B\n"); };
	virtual void DispB(){ printf("b\n"); };
};

class C : public B
{
private:
	char data;
public:
	C(){ data = 'C'; }
	virtual void Show(){ printf("C\n"); };
	virtual void DispC(){ printf("c\n"); };
};

class D : public A, public B, public C
{
public:
	char data;
public:
	D(){ data = 'D'; }
	virtual void Show(){ printf("D\n"); };
	virtual void DispD(){ printf("d\n"); };
};

int main_inheirt()
{
	A* obj = new B;
	obj->Show();

	A* obj2 = new C;
	obj2->Show();

	A* obj3 = new D;
	obj3->Show();

	system("pause");
	return 0;
}