
/*
题目描述
写出一个程序，接受一个由字母和数字组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。

输入描述:
输入一个有字母和数字以及空格组成的字符串，和一个字符。

输出描述:
输出输入字符串中含有该字符的个数。
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