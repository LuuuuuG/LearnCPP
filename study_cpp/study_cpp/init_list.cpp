#include <iostream>
using namespace std;

class base1 {
private: 
	int a, b;
public:
	base1(int i) : b(i + 1), a(b) {}
	base1() :b(0), a(b) {}
	int get_a() { return a; }
	int get_b() { return b; }
};
int main_init_list()
{
	base1 obj1(11);
	cout << obj1.get_a() << endl;//随机数
	cout << obj1.get_b() << endl;//12

	base1 obj2;
	cout << obj2.get_a() << endl;//随机数
	cout << obj2.get_b() << endl;//0

	system("pause");
	return 0;
}