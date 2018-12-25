#include <iostream>
#include <mutex>
using namespace std;

/*
�̰߳�ȫ����ģʽ��

1. �ֲ���̬����ʽ

2. ����ʽ

3. ��������ʽ

*/

//1.�ֲ���̬��Ա ����ʽ
//�ʺ�C++11����֤��̬�ֲ������ĳ�ʼ�����̰߳�ȫ�ġ������C++98�Ͳ��������������
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

//2.����ʽ
//�ŵ㣺�̰߳�ȫ�����ü���Ч�ʸ�
//ȷ���������ʱ�ͳ�ʼ�����˷��ڴ档
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
//�ⲿ��ʼ�� before invoke main
Singleton2* Singleton2::m_instance = new Singleton2();

//3. ���� ����ʽ
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