#include <iostream>
#include <cstdio>
#if 0
namespace test{
	class string
	{
	public:
		/*explicit*/ string(int n);				//������Ԥ�ȷ���n���ֽڸ��ַ���
		string(const char* p);// ��C�����ַ���p��Ϊ��ʼ��ֵ
	};
}

using namespace test;
int main_explicit()
{
	string s1 = "hello";			 //OK ��ʽת�����ȼ���String s1 = String����hello��
	string s2(10);						 //OK ����10���ֽڵĿ��ַ���
	string s3 = string(10);		 //OK ����10���ֽڵĿ��ַ���
	
	string s4 = 10;		//����explicit ����ͨ����Ҳ�Ƿ���10���ֽڵĿ��ַ���
	string s5 = 'a';		//����explicit ����ͨ��������int����a�������ֽڵĿ��ַ���

	system("pause");
	return 0;
}
#endif