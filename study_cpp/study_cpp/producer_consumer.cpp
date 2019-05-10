#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
int i = 0;
std::mutex mtx;
std::condition_variable condition_in, condition_out;
void in(int id)
{
	while (true)
	{
		//(1)
		std::unique_lock<std::mutex> in(mtx);
		condition_in.wait(in, [id](){
			std::cout << "condition_in.wait id:" << id << std::endl;
			return i < 5;
		});
		std::cout << "thread id:" << id << "# " << "===>" << ++i << std::endl;
		//(2)
		condition_out.notify_one();
		//(3)
	}
}
void out(int id)
{
	while (true)
	{
		std::unique_lock<std::mutex> in(mtx);
		condition_out.wait(in, [id](){
			std::cout << "condition_out.wait id: " << id << std::endl;
			return i > 1;
		});
		i -= 2;
		std::cout << "thread id:" << id << "# " << "===>" << i << std::endl;
		condition_in.notify_one();
	}
}

int main_pro_cum()
{
	std::thread t1(in, 0);
	std::thread t2(out, 1);
	//std::thread t3(out,2);
	//std::thread t4(out,3);
	//std::thread t5(out,4);

	t1.join();
	system("pause");
	return 0;
}