#if 0
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string s = "Somewhere down the road";
	istringstream iss(s);

	do
	{
		string subs;
		iss >> subs;
		cout << "Substring: " << subs << endl;
	} while (iss);

	getchar();
	return 0;
}
#endif
//std::copy
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>	//std::copy
#include <iterator>

int main2() {
	using namespace std;
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		ostream_iterator<string>(cout, "\n"));
	getchar();
	return 0;
}