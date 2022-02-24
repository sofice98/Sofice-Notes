/**********
*DP
*Sofice
*2020/7/14
*************/
#include<bits/stdc++.h>
using namespace std;

long long dp[100];

long long fibonacci(int n) {//直接递归版本，到n=40时已经很慢
    if (n == 0 || n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

long long fibonacci_dp(int n) {//DP版本，到n=100时还非常快
    if (n == 0 || n == 1)
        return dp[n] = 1;
    if (dp[n])
        return dp[n];
    return dp[n] = fibonacci_dp(n - 1) + fibonacci_dp(n - 2);
}

int main() {
    memset(dp, 0, sizeof(dp));
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("第%d位斐波那契数为：%lld\n", n, fibonacci_dp(n));
    }
    

    system("pause");
    return 0;
}