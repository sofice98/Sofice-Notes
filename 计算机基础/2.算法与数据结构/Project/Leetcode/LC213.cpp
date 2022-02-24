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
    if (len == 1) return nums[0];
    return max(rob(nums, 0, len - 2), rob(nums, 1, len - 1));
}
int rob(vector<int>& nums, int left, int right) {
    int len = nums.size();
    int prev1 = 0, prev2 = 0, cur;
    for (int i = left; i <= right; i++) {
        cur = max(prev2, prev1 + nums[i]);
        prev1 = prev2; prev2 = cur;
    }
    return cur;
}

int main() {


    system("pause");
    return 0;
}
