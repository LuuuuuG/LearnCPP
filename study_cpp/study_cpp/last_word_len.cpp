/*
��Ŀ����
д��һ�����򣬽���һ������ĸ��������ɵ��ַ�������һ���ַ���Ȼ����������ַ����к��и��ַ��ĸ����������ִ�Сд��

��������:
����һ������ĸ�������Լ��ո���ɵ��ַ�������һ���ַ���

�������:
��������ַ����к��и��ַ��ĸ�����
*/

#include <iostream>
#include <string>
using namespace std;

int main_lwl()
{
	int res = 0;
	string s;
	//cin >> s;
	getline(cin, s);
	for (auto i : s)
	{
		if (i != ' ') {
			res++;
		}
		else {
			res = 0;
		}
	}
	cout << res;
	system("pause");
	return 0;
}