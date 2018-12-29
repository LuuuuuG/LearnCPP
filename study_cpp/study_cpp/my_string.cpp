#include <iostream>
#include <cstring>
using namespace std;

class String{
private:
	char* m_str;
public:
	//1. �޲ι��죺
	String() :m_str(new char[1])
	{
		*m_str = '\0';
	}

	//2. �вι��캯��
	String(const char* str )
		: m_str(new char[strlen(str) + 1])
	{
		strcpy(m_str, str);
	}

	/*
	//ȱʡ�������캯��----ǳ����
	String (string const& that):m_str(that.m_str){}
	*/

	//3. �Զ��忽�����캯��---���
	String(String const& that) 
		: m_str(new char[strlen(that.m_str) + 1])
	{
		strcpy(m_str, that.m_str);
	}

	//4. ������ֵ������---���
	String& operator= (String that) // yes, pass-by-value
	{
		if (&that != this){
			std::swap(m_str, that.m_str);
		}
		return *this;
	}

	//5. ��������
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

	String str2 = str1; //��������
	cout << str2.c_str() << endl;

	String str3("�Ǻ�");
	str2 = str3;//��ֵ
	//	str2 operator= (str3);
	cout << str2.c_str() << endl;

	int a = 10, b = 20, c = 30;
	(a = b) = c;
	cout << a << endl; //30
	system("pause");
	return 0;
}