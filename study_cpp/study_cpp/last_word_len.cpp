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