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


int climbStairs(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    int dp[50] = {0,1,2};
    for (int i = 3; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

int main() {


    system("pause");
    return 0;
}
