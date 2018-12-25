#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
题目：给你一根长度为n的绳子，请把绳子剪成m段 (m和n都是整数，n>1并且m>1)每段绳子的长度记为k[0],k[1],…,k[m]. 请问k[0]k[1]…*k[m]可能的最大乘积是多少？例如，当绳子的长度为8时，我们把它剪成长度分别为2,3,3的三段，此时得到的最大乘积是18.


思路：采用自底向上的动态规划方法。设f(n)代表长度为n的绳子剪成若干段的最大乘积，如果第一刀下去，第一段长度是i，那么剩下的就需要剪n-i，那么f(n)=max{f(i)f(n-i)}。而f(n)的最优解对应着f(i)和f(n-i)的最优解，假如f(i)不是最优解，那么其最优解和f(n-i)乘积肯定大于f(n)的最优解，和f(n)达到最优解矛盾，所以f(n)的最优解对应着f(i)和f(n-i)的最优解。首先，剪绳子是最优解问题，其次，大问题包含小问题，并且大问题的最优解包含着小问题的最优解，所以可以使用动态规划求解问题，并且从小到大求解，把小问题的最优解记录在数组中，求大问题最优解时就可以直接获取，避免重复计算。
    n<2时，由于每次至少减一次，所以返回0。n=2时，只能剪成两个1，那么返回1。n=3时，可以剪成3个1，或者1和2，那么最大乘积是2。当n>3时，就可以使用公式进行求解。
    f(4)=max{f(1)f(3), f(2)f(2)}
    f(5)=max{f(1)f(4), f(2)f(3)}
    ...
    f(n)=max{f(1)f(n-1), f(2)f(n-2), f(3)f(n-3), ..., f(i)(fn-i), ...}

    因为需要保证f(i)f(n-i)不重复，就需要保证i<=n/2，这是一个限制条件，求1～n/2范围内的乘积，得到最大值

*/

int dp_cut_rope(int length)
{
	if (length < 2) return 0;
	if (length == 2) return 1;
	if (length == 3) return 2;

	//if lenght > 3, f(n)=max{f(i)*f(n-i)}
	vector<int> f(length, 0);
	//这些情况下，不剪的时候长度比剪的时候长，所以作为初始条件
	//这些都是子问题最优解,因为是子问题，所以这些情况可以不剪，因为可以看成它是分割后的一部分
	f[0] = 0;
	f[1] = 1;
	f[2] = 2;
	f[3] = 3;
	for (int i = 4; i <= length; ++i)
	{
		int max_val = 0;
		for (int j = 1; j <= length / 2; ++j)
			max_val = max(f[j] * f[i - j], max_val);
		f[i] = max_val;
	}
	return f[length];
}

int main_cut_rope()
{
	int len = 8;
	int res = dp_cut_rope(len);
	cout << res << endl;

	system("pause");
	return 0;
}