#include<bits/stdc++.h>
using namespace std;


void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i + 1] <= nums[i]) {
        i--;
    }
    if (i >= 0) {
        int j = nums.size() - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end());
	return;
}


int main()
{
	vector<int> nums = { 1,3,2 };
	nextPermutation(nums);
	
	return 0;
}