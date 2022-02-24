#include<bits/stdc++.h>
using namespace std;
#define MAX 100010

int trap(vector<int>& height) {
	// 右边最高数
	vector<int> right(height.size());
	// 左边最高数
	vector<int> left(height.size());
	int sum = 0;
	for (int i = 1; i < height.size(); i++) {
		left[i] = (left[i - 1] > height[i - 1]) ? left[i - 1] : height[i - 1];
	}
	for (int i = height.size() - 2; i >= 0; i--) {
		right[i] = (right[i + 1] > height[i + 1]) ? right[i + 1] : height[i + 1];
	}
	for (int i = 0; i < height.size(); i++) {
		int minnum = min(right[i], left[i]);
		if (minnum - height[i] > 0) {
			sum += minnum - height[i];
		}
	}


	return sum;
}

int main()
{
	vector<int> height({ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 });
	trap(height);
	



	return 0;
}