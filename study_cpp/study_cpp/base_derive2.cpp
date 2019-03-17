#include <iostream>

class Base{
public:
	Base(const char* p_szName) : m_szName(p_szName)
	{
		std::cout << m_szName << ",";
	}
	virtual ~Base()
	{
		std::cout << "~" << m_szName << ",";
	}
private:
	const char* m_szName;
};

class Derived : public Base
{
public:
	Derived(const char* p_szName) : m_szName(p_szName)
		, m_objA((const char*) "A")
		, m_objB((const char*) "B")
		, Base((const char*) "C")
	{
		std::cout << m_szName << ",";
	}

	virtual ~Derived()
	{
		std::cout << "~" << m_szName << ",";
	}
private:
	const char* m_szName;
	Base m_objB;
	Base m_objA;
};

int main_B_D2()
{
	Base* p = new Derived("D"); // C B A D
	delete p;// ~D ~A ~B ~C
	std::cout << "\n----------------------\n";
	Derived* q = new Derived("E"); // C B A E
	delete q;// ~E ~A ~B ~C
	system("pause");
	return 0;
}