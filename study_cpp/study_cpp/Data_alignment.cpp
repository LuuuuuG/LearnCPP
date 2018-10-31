#include <iostream>
using namespace std;


class A {
	char k[5];
public:
	virtual void aa() {};
};

class B :  virtual public A {
	char j[6];
public:
	virtual void bb() {};
};

class C : virtual public B {
	//char i[7];
public:
	virtual void cc() {};
};

int main_data_alig() {
	std::cout << "sizeof(A) = " << sizeof(A) << std::endl;//16
	std::cout << "sizeof(B) = " << sizeof(B) << std::endl;//16+24
	std::cout << "sizeof(C) = " << sizeof(C) << std::endl;//16+24+16

	system("pause");
	return 0;
}
