#include<bits/stdc++.h>

using namespace std;

int maxSubArray(vector<int>& nums) {//DP
    int n = nums.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return nums[0];
    int local_max = nums[0];//局部最优
    int global_max = nums[0];//全局最优
    for (int i = 1; i < n; i++) {
        if (local_max < 0)
            local_max = 0;
        local_max += nums[i];
        global_max = max(global_max, local_max);
    }
    return global_max;
}

int maxSubArray(vector<int>& nums) {//Kadane
    int n = nums.size();
    int res = INT_MIN, sum = 0;
    for (int i = 0; i < n; i++){
        sum += nums[i];
        if (res < sum)
            res = sum;
        if (sum < 0)
            sum = 0;
    }
    return res;
}

int main() {
    

    system("pause");
    return 0;
}