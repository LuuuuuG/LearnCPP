#include <iostream>
#include <cstring>
using namespace std;

class String{
private:
	char* m_str;
public:
	//1. 无参构造：
	String() :m_str(new char[1])
	{
		*m_str = '\0';
	}

	//2. 有参构造函数
	String(const char* str )
		: m_str(new char[strlen(str) + 1])
	{
		strcpy(m_str, str);
	}

	/*
	//缺省拷贝构造函数----浅拷贝
	String (string const& that):m_str(that.m_str){}
	*/

	//3. 自定义拷贝构造函数---深拷贝
	String(String const& that) 
		: m_str(new char[strlen(that.m_str) + 1])
	{
		strcpy(m_str, that.m_str);
	}

	//4. 拷贝赋值操作符---深拷贝
	String& operator= (String that) // yes, pass-by-value
	{
		if (&that != this){
			std::swap(m_str, that.m_str);
		}
		return *this;
	}

	//5. 析构函数
	~String(){
		if (m_str){
			delete[] m_str;
			m_str = NULL;
		}
	}

	size_t size() const
	{
		return strlen(m_str);
	}

	const char* c_str(void) const
	{
		return m_str;
	}
};

int main_string()
{
	String str1("Hello,world!");
	cout << str1.c_str() << endl;

	String str2 = str1; //拷贝构造
	cout << str2.c_str() << endl;

	String str3("呵呵");
	str2 = str3;//赋值
	//	str2 operator= (str3);
	cout << str2.c_str() << endl;

	int a = 10, b = 20, c = 30;
	(a = b) = c;
	cout << a << endl; //30
	system("pause");
	return 0;
}