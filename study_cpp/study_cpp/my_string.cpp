#include <iostream>
#include <cstring>
using namespace std;

class String{
public:
	//有参构造函数
	String(char const* str = NULL) :
		m_str(strcpy(new char[
			strlen(str ? str : "") + 1],//str如果为空的处理
				str ? str : "")){}
			/*
			//缺省拷贝构造函数----浅拷贝
			String (string const& that):m_str(that.m_str){}
			*/
			//自定义拷贝构造函数---深拷贝
			String(String const& that) : m_str(strcpy(new char[
				strlen(that.m_str) + 1],
					that.m_str)){}
#if 0
				//拷贝赋值操作符---深拷贝
				//菜鸟版
				/*void operator = (String const& that){
				m_str = new char[
				strlen(that.m_str) + 1];
				strcpy(m_str,that.m_str);
				}*/
				/*
				//小鸟版
				String& operator = (String const& that){
				if(&that != this){ //1 防止自赋值
				delete[] m_str;//2 释放旧资源
				m_str = new char[//3 分配新资源
				strlen(that.m_str) + 1];
				strcpy(m_str,that.m_str);//4 赋值新内容
				}
				return *this;//5 返回自引用
				}
				//缺点：无法保证肯定分配到新资源之前就释放了旧资源
				*/
				//大鸟版
				/*	String& operator = (String const& that){
				if(&that != this){
				char* str = new char[
				strlen(that.m_str) + 1];
				delete[] m_str;
				m_str = strcpy(str,that.m_str);

				}
				return *this;
				}
				*/
#endif
				//老鸟版
				String& operator = (String const& that){
					if (&that != this){
						String str = that;//拷贝构造
						swap(m_str, str.m_str);
					}
					return *this;
				}

				//析构函数
				~String(){
					if (m_str){
						delete[] m_str;
						m_str = NULL;
					}
				}
				char const* c_str(void) const{
					return m_str;
				}
private:
	char* m_str;

};

int main(){
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