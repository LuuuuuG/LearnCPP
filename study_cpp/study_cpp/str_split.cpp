/*
题目描述
•连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
•长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
输入描述:
连续输入字符串(输入2次,每个字符串长度小于100)

输出描述:
输出到长度为8的新字符串数组

示例1
输入
abc
123456789

输出
abc00000
12345678
90000000
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void helper(string s, vector<string> &vec)
{
	int length = s.size() % 8;
	if (length != 0)
	{
		//s.insert(s.end(), 8 - s.szie() % 8, '0');
		string tail(8 - length, '0');
		s += tail;
	}
	for (int i = 0; i < s.size(); i += 8)
	{
		//cout << s.substr(i, 8) << endl;
		string tmp(s.begin() + i, s.begin() + i + 8);
		vec.push_back(tmp);
	}
}

int main_str_split()
{
	vector<string> result;
	string str1;
	string str2;
	cin >> str1;//字符串中有空格时 用getlin(cin, str);
	cin >> str2;
	helper(str1, result);
	helper(str2, result);
	for (auto i : result)
		cout << i << endl;

	return 0;
}