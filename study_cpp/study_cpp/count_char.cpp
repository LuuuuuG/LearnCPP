
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
#include <algorithm>
#include <map>
using namespace std;

int main_cnt_char()
{
	string s;
	
	map<char, int> m;
	//getline(cin, s);
	cin >> s; 
	char ch;
	cin >> ch;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	for (int i = 0; i < s.size() - 1; ++i)
	{
		m[s[i]]++;
	}
	int cnt = m[ch];
	cout << cnt << endl;

	return 0;
}