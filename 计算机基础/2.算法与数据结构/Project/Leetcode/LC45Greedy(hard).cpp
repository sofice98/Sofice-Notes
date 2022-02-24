#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;


//动态规划超时
//int jump(vector<int>& nums) {
//	int size = nums.size();
//	vector<vector<int>> dp(size, vector<int>(size));
//	for (int i = size - 2; i >= 0; i--) {
//		int j;
//		for (j = i + 1; j <= i + nums[i] && j<= size - 1; j++) {
//			dp[i][j] = 1;
//		}
//		for (; j <= size - 1; j++) {
//			int minstep = INT_MAX;
//			for (int k = i + 1; k <= i + nums[i] && k<=size - 1; k++) {
//				if (dp[k][j])	minstep = min(minstep, dp[k][j] + 1);
//				else			minstep = 0;
//			}
//			dp[i][j] = minstep;
//		}
//	}
//
//	return dp[0][size - 1];
//}

//贪心
int jump(vector<int>& nums) {
	int max_end = 0;
	int end = 0;
	int step = 0;
	for (int i = 0; i < nums.size() - 1; i++) {
		max_end = max(max_end, nums[i] + i);
		if (i == end) {
			end = max_end;
			step += 1;
		}
	}
	return step;
}

int main()
{
	vector<int> nums({2,3,1,1,4});
	jump(nums);
	



	return 0;
}