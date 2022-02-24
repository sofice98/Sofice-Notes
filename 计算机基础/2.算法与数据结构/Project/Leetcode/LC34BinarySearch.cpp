#include<bits/stdc++.h>
using namespace std;



int bs(vector<int>& nums, int target, int left, int right) {//¶ş·Ö
	if (left > right)	return -1;
	int mid = (left + right) / 2;
	if (nums[mid] == target)	return mid;
	else if (nums[mid] < target)	return bs(nums, target, mid + 1, right);
	else  return bs(nums, target, left, mid - 1);
}

vector<int> searchRange(vector<int>& nums, int target) {
	if (nums.size() == 0)	return { -1, -1 };
	int left = 0; int right = nums.size() - 1;
	int pl = -1, pr = -1;
	//Íù×óÕÒ¶Ëµã
	int index = bs(nums, target, left, right);
	while (index >= 0) {
		pl = index;
		index = bs(nums, target, left, index - 1);
	}
	//ÍùÓÒÕÒ¶Ëµã
	index = bs(nums, target, left, right);
	while (index >= 0) {
		pr = index;
		index = bs(nums, target, index + 1, right);
	}
	return { pl, pr };
}


int main()
{
	vector<int> nums({ 5,7,7,8,8,10 });
	searchRange(nums, 8);
	
	return 0;
}