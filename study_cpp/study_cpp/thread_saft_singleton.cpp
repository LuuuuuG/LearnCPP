#include <iostream>
#include <mutex>
using namespace std;

/*
线程安全单例模式：

1. 局部静态懒汉式

2. 饿汉式

3. 加锁懒汉式

*/

//1.局部静态成员 懒汉式
//适合C++11，保证静态局部变量的初始化是线程安全的。如果是C++98就不能用这个方法。
class Singleton {
private:
	Singleton() {};
	Singleton(const Singleton &) {};
	Singleton& operator= (const Singleton &);

public:
	static Singleton getInstance()
	{
		static Singleton m_instance;
		return m_instance;
	}
	//test do something
	void doSomething() { cout << "doSomething in Singleton" << endl; }
};

//2.饿汉式
//优点：线程安全，不用加锁效率高
//确定：类加载时就初始化，浪费内存。
class Singleton2
{
private:
	static Singleton2* m_instance;
	Singleton2() {};

public:
	static Singleton2* getInstance()
	{
		return m_instance;
	}
	//test do something
	void doSomething() { cout << "doSomething in Singleton2" << endl; }
};
//外部初始化 before invoke main
Singleton2* Singleton2::m_instance = new Singleton2();

//3. 加锁 懒汉式
class Singleton3
{
private:
	Singleton3() {};
	static Singleton3* m_instance;
	static mutex m_mutex;

public:
	static Singleton3* getInstance()
	{
		if (m_instance == NULL)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_instance == NULL)
				m_instance = new Singleton3();
		}
		return m_instance;
	}
	//test do something
	void doSomething() { cout << "doSomething in Singleton3" << endl; }
};
Singleton3* Singleton3::m_instance = NULL;
mutex Singleton3::m_mutex;

int main_thread_safe_singleton()
{
	Singleton::getInstance().doSomething();
	Singleton2::getInstance()->doSomething();
	Singleton3::getInstance()->doSomething();
	system("pause");
	return 0;
}