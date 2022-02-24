#include<bits/stdc++.h>
using namespace std;

const int N = 1000010;
int s[N] = {};


int removeDuplicates(vector<int>& nums) {
	int p1 = 0;
	int p2 = 1;
	if (nums.empty())
		return 0;
	while (p2 != nums.size()) {
		if (nums[p2] != nums[p1]) {
			nums[++p1] = nums[p2++];
		}
		else {
			p2++;
		}
	}
	return p1 + 1;

}



int main()
{
	vector<int> nums = { 0,1 };
	removeDuplicates(nums);

	
	return 0;
}