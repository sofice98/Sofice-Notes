/**********
*dp
*Sofice
*2020/10/21
***********/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 10000;
constexpr double eps = 1e-7;
#define f(i, a, b) for(int i = a;i <= b;i++)


int rob(vector<int> & nums) {
    int len = nums.size();
    if (len == 0) return 0;
    if (len == 1) return nums[0];
    int dp[105];
    dp[0] = nums[0]; dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < len; i++)
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    return dp[len - 1];
}

int main() {


    system("pause");
    return 0;
}
