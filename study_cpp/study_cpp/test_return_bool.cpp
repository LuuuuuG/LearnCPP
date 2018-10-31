#include <iostream>
#include<vector>
#include <unordered_map>
using namespace std;

int test_return_bool()
{
	bool i = -2;
	cout << i << endl;

	getchar();
	return 0;
}


vector<int> twoSum(vector<int>&nums, int target)
{
#if 0
	//Key is the number and value is its index in the vector.
	unordered_map<int, int> hash;
	vector<int> result;
	for (int i = 0; i < nums.size(); i++) {
		int numberToFind = target - nums[i];

		//if numberToFind is found in map, return them
		if (hash.find(numberToFind) != hash.end()) {
			result.push_back(hash[numberToFind]);
			result.push_back(i);
			return result;
		}

		//number was not found. Put it in the map.
		hash[nums[i]] = i;
	}
	return result;
#else
	std::vector<int> tmp;
	for(int i = 0; i < nums.size(); ++i){
		for (int j = i + 1; j < nums.size(); ++j){
			if (target == nums[i] + nums[j]){
				tmp.push_back(i);
				tmp.push_back(j);
				return tmp;
			}
		}
	}
	return tmp;
#endif
}

int main_test_return_bool()
{
	vector<int> nums{ 2, 7, 11, 15 };
	vector<int> res = twoSum(nums, 18);

	cout << res[0] << " " << res[1] << endl;


	getchar();
	return 0;
}