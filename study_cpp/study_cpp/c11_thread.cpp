//#include "main.h"
#include <iostream>
#include <thread>
#include <string>
#include <mutex> //互斥
#include <fstream>
#include <deque>
#include <condition_variable>
#include <future>
//并发编程 1多进程 多进程(至少一个线程)之间是可以通信的 通信方式 文件 ，管道 消息队列
//			2多线程 一个进程有多个线程 ，线程通过共享内存通信

//优缺点
//线程启动快 进程启动需要系统分配一系列内部资源来管理进程
//线程更轻量级 进程开销较大 进程启动 系统需要对进程添加保护措施
//访问方式 进程访问通过队列和文件 比不过 线程通过共享内存快
//多线程的缺点是 很难管理 而且不能再分布式下运行，进程则可以

#define LOCK_CODE 0 //将代码锁住不让编译
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
//互斥对象
std::mutex mu;

void shared_print(const string &msg, int id)
{
	//////////////////////////////////////////////////////////////////////////

	//当一个线程在打印的时候另一个线程要等待
	//两个对象都访问shared_print是不可能的；
	mu.lock();

	//如果这里发生异常，就永远锁住了；
	cout << msg << id << endl;

	mu.unlock();

	//////////////////////////////////////////////////////////////////////////
	//这个的意思是不管 guard 被析构掉mu会自动解锁 比上面的安全
	std::lock_guard<mutex> guard(mu);
	cout << msg << id << endl;

	//但是cout对象依然会被其他线程访问，我们没有将该线程进行绑定
}

//用这种方式封装后 其他类如果访问这个类就需要等待
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

	//这样是不正确的 不能让这个类暴露在函数之外
	//ofstream &GetStream(return f;)

	//这个函数就暴露在函数之外也是不正确的代码
	//void processf(void fun(ofstream&))
	//{
	//	fun(f);
	//}
private:
	std::mutex m_mutex; //m_mutex保护f
	std::ofstream f;
};

void function_1(LofFile &log)
{
	string newstr = "Hello";
	log.shared_print(newstr, 32);
}

//死锁
std::mutex m_mutex;
std::mutex m_mutex2;
class LogFile2
{
public:

	//主线程调用
	void Shared_Print(string Id, int value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		//std::lock_guard<std::mutex> lock(m_mutex2);

		//可以用std::lock
		//std::lock(m_mutex, m_mutex2);//可以放很多锁
		////但是需要加std::adopt_lock 要获取m_mutex的所有权
		//std::lock_guard<std::mutex> lock(m_mutex,std::adopt_lock);
		//std::lock_guard<std::mutex> lock(m_mutex2, std::adopt_lock);

		cout << Id << value << endl;
	}

	//工作线程调用
	void Shared_Print2(string Id, int value)
	{
		//std::lock_guard<std::mutex> lock(m_mutex2);
		std::lock_guard<std::mutex> lock(m_mutex);

		//解决方式就是顺序要一致
		//std::lock_guard<std::mutex> lock(m_mutex2);
		//std::lock_guard<std::mutex> lock(m_mutex);

		//第二种解决方式 避免死锁
		//可以用std::lock
		//std::lock(m_mutex, m_mutex2);//可以放很多锁
		////但是需要加std::adopt_lock 要获取m_mutex的所有权
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
		//	//如果两个线程访问，一个进入后锁住打开f另一个线程发现!f.is_open() = false所以进入但是被locker锁住等第一个线程完后后退出第二个进入，f被打开两次，这样不安全
		//	std::unique_lock<std::mutex> locker(m_Open, std::defer_lock);//
		//	f.open("log.txt");
		//}
		{
			//这样虽然安全了但是频繁的上锁对计算机消耗蛮大的，可以使用	std::once_flag m_flg;
			std::unique_lock<std::mutex> locker(m_Open, std::defer_lock);
			if (!f.is_open())
			{
				f.open("log.txt");
			}
		}

		//这个函数确保f.open("log.txt"); 被调用一次
		std::call_once(m_flg, [&]() {f.open("log.txt"); });

		//	std::lock_guard<std::mutex> lock(m_mutex);
		//std::defer_lock 告诉m_mutex并没有被锁住
		std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);//比lock_guard更具有弹性 
		cout << "Hello" << endl; //只锁住打印
		locker.lock();//为制定的代码添加锁
		cout << "Hello" << endl;
		locker.unlock();
		//有很多执行代码，但是不想这些代码被锁住,可以使用		locker.unlock();
		locker.lock();
		//...
		locker.unlock();

		//lock_guard 和 unique_lock 都不能被复制 但是unique_lock可以移动move ,lock_guard不能
		//当我们移动unique_lock 它会将控制权从一个unique_lock 转移到另一个

		std::unique_lock<std::mutex> locker2 = std::move(locker);

		//lock_guard 比 unique_lock消耗小，所以使用lock_guard的频率高
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

//生产者
void Funcation_One()
{
	int count = 10;
	while (count > 9)
	{
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		//	cond.notify_one();//经过的时候通知其他线程 但是要配合wait，但只能激活一个线程 如果想激活多个
		cond.notify_all();//激活所有等待线程
		locker.unlock();
		std::this_thread::sleep_for(chrono::seconds(1));//线程休眠1s
		count--;
	}
}

//销毁者
void Funcation_Two()
{
	int data = 0;
	while (data != 1)//无效的循环是非常低效率的
	{
		std::unique_lock<mutex> locker(mu);//枷锁必须
		//if (!q.empty())
		//{
		//	cond.wait(locker);//接受等待的线程，不需要手动设置时间 会将线程休眠直到有调用notify_one时候唤醒，线程不会被加锁后休眠所以需要一个locker解锁后休眠等唤醒再加锁，只能使用unique_lock，不能使用lock_guard，lock_guard不能重复加解锁
		cond.wait(locker, [](){return !q.empty(); });//需要添加一个条件  [](){return !q.empty(); 防止猥激活
		data = q.back();
		q.pop_back();//弹出
		locker.unlock();
		cout << "T2 Got a value from t1:" << data << endl;
		/*	}*/
		//else
		//{
		//	locker.unlock();//为空才解锁
		//	//std::this_thread::sleep_for(chrono::seconds(10));//添加休眠，但是要休眠多久不清楚，所以需要一个条件变量
		//}
	}
}

//阶乘函数
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
	int N = f.get(); //从子线程获取主线程变量
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
	int N = f.get(); //从子线程获取主线程变量
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
std::condition_variable conds;//需要条件变量防止子线程比主线程执行快
void thread_1()
{
	std::packaged_task<int()> t;
	{
		//锁住
		std::unique_lock <std::mutex> locker(mu);
		conds.wait(locker, [] {return !Task_q.empty(); });//条件变量需要使用unique_lock
		t = std::move(Task_q.front());//弹出队列函数
	}
	t();//执行该函数
}

int main_thread()
{
	//简单线程//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE

	thread t1(Fun);

	//	t1.join();//主线程会等待知道t1的线程执行完毕后再执行主线程
	t1.detach();//主线程不需要等待，而是直接运行，主线程会运行比较快 t1线程没有来得及运行就结束了 一旦线程被detach 就不能join了 否则会奔溃

	//判断当前t1可以被join吗 ？
	if (t1.joinable())
	{
		t1.join();
	}

#endif

	//线程管理//////////////////////////////////////////////////////////////////////////

#if LOCK_CODE

	Fctor fct;
	string s = "I Love You";
	//thread t1(Fctor(), s);//线程开始
	//thread t1(fct, s);//并不会传递引用，在子线程内并不会去修改这个值
	//thread t1(fct, std::ref(s));//s 如果想通过引用需要添加ref
	thread t1(fct, std::move(s));//move 是安全高效的方式，可以让一个线程内的资源赋值给另一个，因为线程对象只能被移动不能被复制
	//thread t2 = t1;//线程对象只能被移动不能被复制
	//thread t2 =std::move(t1);这样就可以将线程t1赋值给t2; 
	//t1.join();
	//每个线程都有id

	cout << this_thread::get_id() << endl;//获取主线程ID
	cout << t1.get_id() << endl;		//t1线程的ID

	//需要创建多少线程呢？要根据CPU数目
	//thread::hardware_concurrency() 这个可以获取你到底可以使用多少线程
	cout << "可以创建的线程数目是：" << thread::hardware_concurrency() << endl;
	
	//捕捉异常后通知类现场Fctor
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
	//数据竞争和互斥////////////////////////////////////////////////////////////////////////

#if LOCK_CODE

	LofFile log;
	thread t2(function_1, std::ref(log));
	for (int i = 0; i < 100; i++)
	{
		log.shared_print("main :", 22);
	}
#endif

	//死锁	//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	LogFile2 log;
	//工作线程调用
	thread t2(function_2, std::ref(log));
	//主线程调用，相互等待解锁
	for (int i = 0; i < 100; i++)
	{
		log.Shared_Print("main :", 22);
	}
#endif

	//主线程获取子线程变量////////////////////////////////////////////////////////////////////////	
#if LOCK_CODE
	int x;
	//	std::thread t1(factorial, 4, std::ref(x)); //这种方式不好
	//	t1.join();
	std::future<int> fu = std::async(factorial1, 4); //需要函数有返回值 //async不一定会创建子线程取决与第一个参数
	//async(launch::deferred, factorial1, 4);延迟调用，当调用fu.get();才会调用factorial1，并且在一个线程里面
	//async(launch::async, factorial1, 4);//创建一个线程来执行函数
	//async(launch::async | launch::deferred, factorial1, 4);//创建子线程取决于实现
	x = fu.get();//返回子线程的结果
	//fu.get()只能调用一次，第二次就奔溃；
#endif

	//子线程获取主线程变量////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	std::promise<int> p;//一个承诺 后面必须要用set_value 否则 子线程 int N = f.get(); 的时候会抛出一个异常 
	//promise future 只能move 不能Copy
	//std::promise<int> p2 = p;//错误
	//std::promise<int> p2 = std::move( p);//正确
	std::future<int> f = p.get_future();//从未来获取p变量
	std::future<int> fus = std::async(factorial2, std::ref(f));

	p.set_value(4);
	x = fus.get();//主线程获取子线程数据
	cout << "Get form child" << x << endl;

	//对于多线程 如果有十个////////////////////////////////////////////////////////////////////////
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//...
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//std::future<int> fus = std::async(launch::async,factorial2, std::ref(f));
	//标准库提供该功能
	std::shared_future<int> sf = f.share();//shared_future可以被Copy 可以值传递
	std::future<int> fus1 = std::async(launch::async, factorial3, std::ref(f));
	std::future<int> fus2 = std::async(launch::async, factorial3, std::ref(f));
	std::future<int> fus3 = std::async(launch::async, factorial3, std::ref(f));
	//可以创建多个
#endif

	//主线程创建子线程方式总结////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	A a;
	std::thread t1(a, 6);//传递a的拷贝传递给子线程
	std::thread t2(std::ref(a), 6);//传递a引用给子线程
	std::thread t3(std::move(a), 6);//将主线程a移动到子线程,a在主线程不再有效
	std::thread t4(A(), 6);//传递临时创建的a对象给子线程 当然也可以传递函数
	std::thread t5(foo, 6);//函数
	std::thread t6([](int x) {return x & x; }, 6);//也可以用lamada函数创建一个子线程
	std::thread t7(&A::f, a, 8, 'w');//传递A的拷贝成员给子线程
	std::thread t7(&A::f, &a, 8, 'w');//传递a的地址传递子线程
	std::async(std::launch::async, a, 6);//通过异步创建线程
#endif

	//////////////////////////////////////////////////////////////////////////
#if LOCK_CODE
	//通过函数对象调用该函数 但是不是异步的
	auto t1 = std::bind(factorial, 6);
	t1();

	//是异步调用对象 并且可以通过异步获取future： std::future<int> ret = t.get_future();
	std::packaged_task<int()> t(std::bind(factorial, 6));

	//案例：//////////////////////////////////////////////////////////////////////////
	std::thread t2(thread_1);//创建子线程
	std::packaged_task<int()> t(std::bind(factorial1, 6));
	std::future<int> ret = t.get_future();//获取与packaged_task 共享状态相关联的 future 对象

	{
		//访问该共享数据的时候加锁
		std::lock_guard<std::mutex> locker(mu);
		//Task_q.push_back(t);
		Task_q.push_back(std::move(t));//主线程不再使用t就放在子线程里面使用
	}
	cond.notify_one(); //这样绝对线程安全 当执行完毕push_back后通知子线程执行move

	//获取异步返回值
	int value = ret.get();

	//主线程等待t2执行完毕后执行主线程
	t2.join();

	//std::thread t1(factoral, 6);
	//	std::packaged_task<int(int)> t(factorial);

	//	std::packaged_task<int(int)> t(factorial); 执行的结果由另一个线程获取 异步访问
#endif

#if LOCK_CODE
	//时间限制
	//////////////////////////////////////////////////////////////////////////
	std::thread t1(factorial, 6);//创建一个子线程
	std::this_thread::sleep_for(chrono::milliseconds(3));//休眠3毫秒

	//让该线程休眠4毫秒
	chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
	std::this_thread::sleep_until(tp);

	//锁也有时间限制
	std::unique_lock<std::mutex> locker(mu);
	//locker.try_lock_for(chrono::microseconds(3));
	//locker.try_lock_until(tp);

	//条件锁时间限制
	std::condition_variable cond_text;
	cond_text.wait_for(locker, chrono::microseconds(3));
	cond_text.wait_until(locker, tp);

	//承诺的时间限制
	std::promise<int> p;
	std::future<int> f = p.get_future();
	f.wait_for(chrono::microseconds(3));
	f.wait_until(tp);
#endif

	system("pause");
	return 0;
};