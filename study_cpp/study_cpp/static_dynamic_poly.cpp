#include <iostream>

/*
��̬��ָ��ͬ�����յ���ͬ��Ϣ��ͬ�����յ���ͬ��Ϣʱ������ͬ��ʵ�ֶ�����C++֧�����ֶ�̬�ԣ�����ʱ��̬�ԣ�����ʱ��̬�ԡ�

����ʱ��̬�ԣ���̬��̬����ͨ�����غ���ʵ�֣��������� early binding
����ʱ��̬�ԣ���̬��̬����ͨ���麯��ʵ�� ���ͺ����� late binding
--from: https://zhuanlan.zhihu.com/p/37340242

��̬��֮�����ڶ�̬�������ڶ�̬(C++��): https://blog.csdn.net/dan15188387481/article/details/49667389
*/

#if 0
// ��1������ģ�����ֳ������ڶ�̬
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
// ��2���麯���ͼ̳й�ϵ���������ڶ�̬

class parent
{
public:
	parent() {}

	// ������麯��
	virtual void eat()
	{
		std::cout << "Parent eat." << std::endl;
	}

	// ע������������麯��������
	void drink()
	{
		std::cout << "Parent drink." << std::endl;
	}
};

class child : public parent
{
public:
	child() {}

	// ������д�˸�����麯��
	void eat()
	{
		std::cout << "Child eat." << std::endl;
	}

	// ���า���˸���ĺ�����ע�����ڸ�����������
	// �������麯�������Բ����ڼ̳к���д��˵��
	void drink()
	{
		std::cout << "Child drink." << std::endl;
	}

	// �������еĺ���
	void childLove()
	{
		std::cout << "Child love playing." << std::endl;
	}
};

int main_static_dyna_poly()
{
	parent* pa = new child();
	pa->eat();		// �����ڶ�̬�����֣�����
	pa->drink();	// ������õĻ��Ǹ����drink�����Բ����Ƕ�̬������
	// pa->childLove(); // ������������ָ�벻�ܵ��ø���û�еĺ���

	system("pause");
	return 0;
}

#endif