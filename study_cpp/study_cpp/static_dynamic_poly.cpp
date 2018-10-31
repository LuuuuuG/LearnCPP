#include <iostream>

/*
多态性指相同对象收到不同消息或不同对象收到相同消息时产生不同的实现动作。C++支持两种多态性：编译时多态性，运行时多态性。

编译时多态性（静态多态）：通过重载函数实现：先期联编 early binding
运行时多态性（动态多态）：通过虚函数实现 ：滞后联编 late binding
--from: https://zhuanlan.zhihu.com/p/37340242

多态性之编译期多态和运行期多态(C++版): https://blog.csdn.net/dan15188387481/article/details/49667389
*/

#if 0
// 例1：函数模板体现出编译期多态
template <typename T>
T add(T a, T b)
{
	T c = a + b;
	return c;
}

int main()
{
	int i1 = 1;
	int i2 = 2;
	int iResult = 0;

	iResult = add(i1, i2);
	std::cout << "The result of integer is " << iResult << std::endl;

	double d1 = 1.1;
	double d2 = 2.2;
	double dResult = 0;

	dResult = add(d1, d2);
	std::cout << "The result of double  is " << dResult << std::endl;

	system("pause");
	return 0;
}

#else
// 例2：虚函数和继承关系体现运行期多态

class parent
{
public:
	parent() {}

	// 父类的虚函数
	virtual void eat()
	{
		std::cout << "Parent eat." << std::endl;
	}

	// 注意这个并不是虚函数！！！
	void drink()
	{
		std::cout << "Parent drink." << std::endl;
	}
};

class child : public parent
{
public:
	child() {}

	// 子类重写了父类的虚函数
	void eat()
	{
		std::cout << "Child eat." << std::endl;
	}

	// 子类覆盖了父类的函数，注意由于父类的这个函数
	// 并不是虚函数，所以不存在继承后重写的说法
	void drink()
	{
		std::cout << "Child drink." << std::endl;
	}

	// 子类特有的函数
	void childLove()
	{
		std::cout << "Child love playing." << std::endl;
	}
};

int main_static_dyna_poly()
{
	parent* pa = new child();
	pa->eat();		// 运行期多态的体现！！！
	pa->drink();	// 这里调用的还是父类的drink，所以并不是多态！！！
	// pa->childLove(); // 编译出错，父类的指针不能调用父类没有的函数

	system("pause");
	return 0;
}

#endif