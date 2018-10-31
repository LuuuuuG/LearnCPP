#include <iostream>
#include <cstdio>
#if 0
namespace test{
	class string
	{
	public:
		/*explicit*/ string(int n);				//本意是预先分配n个字节给字符串
		string(const char* p);// 用C风格的字符串p作为初始化值
	};
}

using namespace test;
int main_explicit()
{
	string s1 = "hello";			 //OK 隐式转换，等价于String s1 = String（”hello”
	string s2(10);						 //OK 分配10个字节的空字符串
	string s3 = string(10);		 //OK 分配10个字节的空字符串
	
	string s4 = 10;		//不加explicit 编译通过，也是分配10个字节的空字符串
	string s5 = 'a';		//不加explicit 编译通过，分配int（‘a’）个字节的空字符串

	system("pause");
	return 0;
}
#endif