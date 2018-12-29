#include <iostream>
#include <cstring>
using namespace std;

class String{
public:
	//�вι��캯��
	String(char const* str = NULL) :
		m_str(strcpy(new char[
			strlen(str ? str : "") + 1],//str���Ϊ�յĴ���
				str ? str : "")){}
			/*
			//ȱʡ�������캯��----ǳ����
			String (string const& that):m_str(that.m_str){}
			*/
			//�Զ��忽�����캯��---���
			String(String const& that) : m_str(strcpy(new char[
				strlen(that.m_str) + 1],
					that.m_str)){}
#if 0
				//������ֵ������---���
				//�����
				/*void operator = (String const& that){
				m_str = new char[
				strlen(that.m_str) + 1];
				strcpy(m_str,that.m_str);
				}*/
				/*
				//С���
				String& operator = (String const& that){
				if(&that != this){ //1 ��ֹ�Ը�ֵ
				delete[] m_str;//2 �ͷž���Դ
				m_str = new char[//3 ��������Դ
				strlen(that.m_str) + 1];
				strcpy(m_str,that.m_str);//4 ��ֵ������
				}
				return *this;//5 ����������
				}
				//ȱ�㣺�޷���֤�϶����䵽����Դ֮ǰ���ͷ��˾���Դ
				*/
				//�����
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
				//�����
				String& operator = (String const& that){
					if (&that != this){
						String str = that;//��������
						swap(m_str, str.m_str);
					}
					return *this;
				}

				//��������
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