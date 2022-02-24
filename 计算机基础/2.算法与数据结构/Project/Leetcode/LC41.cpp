#include<bits/stdc++.h>
using namespace std;

//每次循环把一个数字放到该放的地方
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
            swap(nums[i], nums[nums[i] - 1]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

int main()
{
	vector<int> nums({ 3,4,-1,1 });
	firstMissingPositive(nums);
	
	return 0;
}