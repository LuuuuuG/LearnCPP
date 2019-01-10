//#include "main.h"
#include <iostream>
#include <thread>
#include <string>
#include <mutex> //����
#include <fstream>
#include <deque>
#include <condition_variable>
#include <future>
//������� 1����� �����(����һ���߳�)֮���ǿ���ͨ�ŵ� ͨ�ŷ�ʽ �ļ� ���ܵ� ��Ϣ����
//			2���߳� һ�������ж���߳� ���߳�ͨ�������ڴ�ͨ��

//��ȱ��
//�߳������� ����������Ҫϵͳ����һϵ���ڲ���Դ���������
//�̸߳������� ���̿����ϴ� �������� ϵͳ��Ҫ�Խ�����ӱ�����ʩ
//���ʷ�ʽ ���̷���ͨ�����к��ļ� �Ȳ��� �߳�ͨ�������ڴ��
//���̵߳�ȱ���� ���ѹ��� ���Ҳ����ٷֲ�ʽ�����У����������

#define LOCK_CODE 0 //��������ס���ñ���
using namespace std;

//////////////////////////////////////////////////////////////////////////
void Fun()
{
	cout << "Hello" << endl;
}

class Fctor
{
public:
	void operator()(const string &msg)
	{
		for (int i = 0; i < 100; ++i)
		{
			cout << "From T1:" + msg + " " + to_string(i) << endl;
		}
	}
};

//////////////////////////////////////////////////////////////////////////
//�������
std::mutex mu;

void shared_print(const string &msg, int id)
{
	//////////////////////////////////////////////////////////////////////////

	//��һ���߳��ڴ�ӡ��ʱ����һ���߳�Ҫ�ȴ�
	//�������󶼷���shared_print�ǲ����ܵģ�
	mu.lock();

	//������﷢���쳣������Զ��ס�ˣ�
	cout << msg << id << endl;

	mu.unlock();

	//////////////////////////////////////////////////////////////////////////
	//�������˼�ǲ��� guard ��������mu���Զ����� ������İ�ȫ
	std::lock_guard<mutex> guard(mu);
	cout << msg << id << endl;

	//����cout������Ȼ�ᱻ�����̷߳��ʣ�����û�н����߳̽��а�
}

//�����ַ�ʽ��װ�� ���������������������Ҫ�ȴ�
class LofFile
{
public:
	LofFile()
	{
		f.open("log.txt");
	}

	~LofFile()
	{
		f.close();
	}

	void shared_print(const string &msg, int id)
	{
		lock_guard<mutex> locker(m_mutex);
		f << msg << id << endl;
	}

	//�����ǲ���ȷ�� ����������౩¶�ں���֮��
	//ofstream &GetStream(return f;)

	//��������ͱ�¶�ں���֮��Ҳ�ǲ���ȷ�Ĵ���
	//void processf(void fun(ofstream&))
	//{
	//	fun(f);
	//}
private:
	std::mutex m_mutex; //m_mutex����f
	std::ofstream f;
};

void function_1(LofFile &log)
{
	string newstr = "Hello";
	log.shared_print(newstr, 32);
}

//����
std::mutex m_mutex;
std::mutex m_mutex2;
class LogFile2
{
public:

	//���̵߳���
	void Shared_Print(string Id, int value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		//std::lock_guard<std::mutex> lock(m_mutex2);

		//������std::lock
		//std::lock(m_mutex, m_mutex2);//���Էźܶ���
		////������Ҫ��std::adopt_lock Ҫ��ȡm_mutex������Ȩ
		//std::lock_guard<std::mutex> lock(m_mutex,std::adopt_lock);
		//std::lock_guard<std::mutex> lock(m_mutex2, std::adopt_lock);

		cout << Id << value << endl;
	}

	//�����̵߳���
	void Shared_Print2(string Id, int value)
	{
		//std::lock_guard<std::mutex> lock(m_mutex2);
		std::lock_guard<std::mutex> lock(m_mutex);

		//�����ʽ����˳��Ҫһ��
		//std::lock_guard<std::mutex> lock(m_mutex2);
		//std::lock_guard<std::mutex> lock(m_mutex);

		//�ڶ��ֽ����ʽ ��������
		//������std::lock
		//std::lock(m_mutex, m_mutex2);//���Էźܶ���
		////������Ҫ��std::adopt_lock Ҫ��ȡm_mutex������Ȩ
		//std::lock_guard<std::mutex> lock(m_mutex2,std::adopt_lock);
		//std::lock_guard<std::mutex> lock(m_mutex, std::adopt_lock);

		cout << Id << value << endl;
	}


};

class LogFile3
{
public:
	LogFile3()
	{

	}
	void Shared_Print(string Id, int value)
	{
		//if (!f.is_open())
		//{
		//	//��������̷߳��ʣ�һ���������ס��f��һ���̷߳���!f.is_open() = false���Խ��뵫�Ǳ�locker��ס�ȵ�һ���߳������˳��ڶ������룬f�������Σ���������ȫ
		//	std::unique_lock<std::mutex> locker(m_Open, std::defer_lock);//
		//	f.open("log.txt");
		//}
		{
			//������Ȼ��ȫ�˵���Ƶ���������Լ������������ģ�����ʹ��	std::once_flag m_flg;
			std::unique_lock<std::mutex> locker(m_Open, std::defer_lock);
			if (!f.is_open())
			{
				f.open("log.txt");
			}
		}

		//�������ȷ��f.open("log.txt"); ������һ��
		std::call_once(m_flg, [&]() {f.open("log.txt"); });

		//	std::lock_guard<std::mutex> lock(m_mutex);
		//std::defer_lock ����m_mutex��û�б���ס
		std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);//��lock_guard�����е��� 
		cout << "Hello" << endl; //ֻ��ס��ӡ
		locker.lock();//Ϊ�ƶ��Ĵ��������
		cout << "Hello" << endl;
		locker.unlock();
		//�кܶ�ִ�д��룬���ǲ�����Щ���뱻��ס,����ʹ��		locker.unlock();
		locker.lock();
		//...
		locker.unlock();

		//lock_guard �� unique_lock �����ܱ����� ����unique_lock�����ƶ�move ,lock_guard����
		//�������ƶ�unique_lock ���Ὣ����Ȩ��һ��unique_lock ת�Ƶ���һ��

		std::unique_lock<std::mutex> locker2 = std::move(locker);

		//lock_guard �� unique_lock����С������ʹ��lock_guard��Ƶ�ʸ�
	}

	std::ofstream f;
	std::mutex m_Open;
	std::once_flag m_flg;
};

void function_2(LogFile2 &log)
{
	string newstr = "Hello";
	log.Shared_Print(newstr, 32);
}

std::deque<int> q;
std::mutex m_Mu;
std::condition_variable cond;

//������
void Funcation_One()
{
	int count = 10;
	while (count > 9)
	{
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		//	cond.notify_one();//������ʱ��֪ͨ�����߳� ����Ҫ���wait����ֻ�ܼ���һ���߳� ����뼤����
		cond.notify_all();//�������еȴ��߳�
		locker.unlock();
		std::this_thread::sleep_for(chrono::seconds(1));//�߳�����1s
		count--;
	}
}

//������
void Funcation_Two()
{
	int data = 0;
	while (data != 1)//��Ч��ѭ���Ƿǳ���Ч�ʵ�
	{
		std::unique_lock<mutex> locker(mu);//��������
		//if (!q.empty())
		//{
		//	cond.wait(locker);//���ܵȴ����̣߳�����Ҫ�ֶ�����ʱ�� �Ὣ�߳�����ֱ���е���notify_oneʱ���ѣ��̲߳��ᱻ����������������Ҫһ��locker���������ߵȻ����ټ�����ֻ��ʹ��unique_lock������ʹ��lock_guard��lock_guard�����ظ��ӽ���
		cond.wait(locker, [](){return !q.empty(); });//��Ҫ���һ������  [](){return !q.empty(); ��ֹ⫼���
		data = q.back();
		q.pop_back();//����
		locker.unlock();
		cout << "T2 Got a value from t1:" << data << endl;
		/*	}*/
		//else
		//{
		//	locker.unlock();//Ϊ�ղŽ���
		//	//std::this_thread::sleep_for(chrono::seconds(10));//������ߣ�����Ҫ���߶�ò������������Ҫһ����������
		//}
	}
}

//�׳˺���
void factorial(int N)
{
	int res = 1;
	for (int i = N; i>1; i--)
	{
		res *= i;
	}
	cout << "Result Is :" << res << endl;
}

int factorial1(int N)
{
	int res = 1;
	for (int i = N; i > 1; i--)
	{
		res *= i;
	}
	cout << "Result Is :" << res << endl;

	return res;
}

int factorial2(std::future<int> &f)
{
	int res = 1;
	int N = f.get(); //�����̻߳�ȡ���̱߳���
	for (int i = N; i > 1; i--)
	{
		res *= i;
	}
	cout << "Result Is :" << res << endl;

	return res;
}

int factorial3(std::shared_future<int> &f)
{
	int res = 1;
	int N = f.get(); //�����̻߳�ȡ���̱߳���
	for (int i = N; i > 1; i--)
	{
		res *= i;
	}
	cout << "Result Is :" << res << endl;

	return res;
}

class A
{

public:

	void f(int x, char c){}
	int operator()(int N) { return 0; }
};

void foo(int x) {}

int factoral(int N)
{
	int res = 1;

	for (int i = N; i>1; i--)
	{
		res *= i;
	}
	cout << "Result is:" << res << endl;

	return res;
}

std::deque<std::packaged_task<int()>> Task_q;
std::mutex mu_c;
std::condition_variable conds;//��Ҫ����������ֹ���̱߳����߳�ִ�п�
void thread_1()
{
	std::packaged_task<int()> t;
	{
		//��ס
		std::unique_lock <std::mutex> locker(mu);
		conds.wait(locker, [] {return !Task_q.empty(); });//����������Ҫʹ��unique_lock
		t = std::move(Task_q.front());//�������к���
	}
	t();//ִ�иú���
}

int main_thread()
{
	//���߳�//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE

	thread t1(Fun);

	//	t1.join();//���̻߳�ȴ�֪��t1���߳�ִ����Ϻ���ִ�����߳�
	t1.detach();//���̲߳���Ҫ�ȴ�������ֱ�����У����̻߳����бȽϿ� t1�߳�û�����ü����оͽ����� һ���̱߳�detach �Ͳ���join�� ����ᱼ��

	//�жϵ�ǰt1���Ա�join�� ��
	if (t1.joinable())
	{
		t1.join();
	}

#endif

	//�̹߳���//////////////////////////////////////////////////////////////////////////

#if LOCK_CODE

	Fctor fct;
	string s = "I Love You";
	//thread t1(Fctor(), s);//�߳̿�ʼ
	//thread t1(fct, s);//�����ᴫ�����ã������߳��ڲ�����ȥ�޸����ֵ
	//thread t1(fct, std::ref(s));//s �����ͨ��������Ҫ���ref
	thread t1(fct, std::move(s));//move �ǰ�ȫ��Ч�ķ�ʽ��������һ���߳��ڵ���Դ��ֵ����һ������Ϊ�̶߳���ֻ�ܱ��ƶ����ܱ�����
	//thread t2 = t1;//�̶߳���ֻ�ܱ��ƶ����ܱ�����
	//thread t2 =std::move(t1);�����Ϳ��Խ��߳�t1��ֵ��t2; 
	//t1.join();
	//ÿ���̶߳���id

	cout << this_thread::get_id() << endl;//��ȡ���߳�ID
	cout << t1.get_id() << endl;		//t1�̵߳�ID

	//��Ҫ���������߳��أ�Ҫ����CPU��Ŀ
	//thread::hardware_concurrency() ������Ի�ȡ�㵽�׿���ʹ�ö����߳�
	cout << "���Դ������߳���Ŀ�ǣ�" << thread::hardware_concurrency() << endl;
	
	//��׽�쳣��֪ͨ���ֳ�Fctor
	try
	{
		for (int i = 0; i <100; i++)
		{
			cout << "From Main" << i << endl;
		}
	}
	catch (...)
	{
		t1.join();
	}

#endif
	//���ݾ����ͻ���////////////////////////////////////////////////////////////////////////

#if LOCK_CODE

	LofFile log;
	thread t2(function_1, std::ref(log));
	for (int i = 0; i < 100; i++)
	{
		log.shared_print("main :", 22);
	}
#endif

	//����	//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	LogFile2 log;
	//�����̵߳���
	thread t2(function_2, std::ref(log));
	//���̵߳��ã��໥�ȴ�����
	for (int i = 0; i < 100; i++)
	{
		log.Shared_Print("main :", 22);
	}
#endif

	//���̻߳�ȡ���̱߳���////////////////////////////////////////////////////////////////////////	
#if LOCK_CODE
	int x;
	//	std::thread t1(factorial, 4, std::ref(x)); //���ַ�ʽ����
	//	t1.join();
	std::future<int> fu = std::async(factorial1, 4); //��Ҫ�����з���ֵ //async��һ���ᴴ�����߳�ȡ�����һ������
	//async(launch::deferred, factorial1, 4);�ӳٵ��ã�������fu.get();�Ż����factorial1��������һ���߳�����
	//async(launch::async, factorial1, 4);//����һ���߳���ִ�к���
	//async(launch::async | launch::deferred, factorial1, 4);//�������߳�ȡ����ʵ��
	x = fu.get();//�������̵߳Ľ��
	//fu.get()ֻ�ܵ���һ�Σ��ڶ��ξͱ�����
#endif

	//���̻߳�ȡ���̱߳���////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	std::promise<int> p;//һ����ŵ �������Ҫ��set_value ���� ���߳� int N = f.get(); ��ʱ����׳�һ���쳣 
	//promise future ֻ��move ����Copy
	//std::promise<int> p2 = p;//����
	//std::promise<int> p2 = std::move( p);//��ȷ
	std::future<int> f = p.get_future();//��δ����ȡp����
	std::future<int> fus = std::async(factorial2, std::ref(f));

	p.set_value(4);
	x = fus.get();//���̻߳�ȡ���߳�����
	cout << "Get form child" << x << endl;

	//���ڶ��߳� �����ʮ��////////////////////////////////////////////////////////////////////////
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//...
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//��׼���ṩ�ù���
	std::shared_future<int> sf = f.share();//shared_future���Ա�Copy ����ֵ����
	std::future<int> fus1 = std::async(launch::async, factorial3, std::ref(f));
	std::future<int> fus2 = std::async(launch::async, factorial3, std::ref(f));
	std::future<int> fus3 = std::async(launch::async, factorial3, std::ref(f));
	//���Դ������
#endif

	//���̴߳������̷߳�ʽ�ܽ�////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	A a;
	std::thread t1(a, 6);//����a�Ŀ������ݸ����߳�
	std::thread t2(std::ref(a), 6);//����a���ø����߳�
	std::thread t3(std::move(a), 6);//�����߳�a�ƶ������߳�,a�����̲߳�����Ч
	std::thread t4(A(), 6);//������ʱ������a��������߳� ��ȻҲ���Դ��ݺ���
	std::thread t5(foo, 6);//����
	std::thread t6([](int x) {return x & x; }, 6);//Ҳ������lamada��������һ�����߳�
	std::thread t7(&A::f, a, 8, 'w');//����A�Ŀ�����Ա�����߳�
	std::thread t7(&A::f, &a, 8, 'w');//����a�ĵ�ַ�������߳�
	std::async(std::launch::async, a, 6);//ͨ���첽�����߳�
#endif

	//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	//ͨ������������øú��� ���ǲ����첽��
	auto t1 = std::bind(factorial, 6);
	t1();

	//���첽���ö��� ���ҿ���ͨ���첽��ȡfuture�� std::future<int> ret = t.get_future();
	std::packaged_task<int()> t(std::bind(factorial, 6));

	//������//////////////////////////////////////////////////////////////////////////
	std::thread t2(thread_1);//�������߳�
	std::packaged_task<int()> t(std::bind(factorial1, 6));
	std::future<int> ret = t.get_future();//��ȡ��packaged_task ����״̬������� future ����

	{
		//���ʸù������ݵ�ʱ�����
		std::lock_guard<std::mutex> locker(mu);
		//Task_q.push_back(t);
		Task_q.push_back(std::move(t));//���̲߳���ʹ��t�ͷ������߳�����ʹ��
	}
	cond.notify_one(); //���������̰߳�ȫ ��ִ�����push_back��֪ͨ���߳�ִ��move

	//��ȡ�첽����ֵ
	int value = ret.get();

	//���̵߳ȴ�t2ִ����Ϻ�ִ�����߳�
	t2.join();

	//std::thread t1(factoral, 6);
	//	std::packaged_task<int(int)> t(factorial);

	//	std::packaged_task<int(int)> t(factorial); ִ�еĽ������һ���̻߳�ȡ �첽����
#endif

#if LOCK_CODE
	//ʱ������
	//////////////////////////////////////////////////////////////////////////
	std::thread t1(factorial, 6);//����һ�����߳�
	std::this_thread::sleep_for(chrono::milliseconds(3));//����3����

	//�ø��߳�����4����
	chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
	std::this_thread::sleep_until(tp);

	//��Ҳ��ʱ������
	std::unique_lock<std::mutex> locker(mu);
	//locker.try_lock_for(chrono::microseconds(3));
	//locker.try_lock_until(tp);

	//������ʱ������
	std::condition_variable cond_text;
	cond_text.wait_for(locker, chrono::microseconds(3));
	cond_text.wait_until(locker, tp);

	//��ŵ��ʱ������
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.wait_for(chrono::microseconds(3));
	f.wait_until(tp);
#endif

	system("pause");
	return 0;
};