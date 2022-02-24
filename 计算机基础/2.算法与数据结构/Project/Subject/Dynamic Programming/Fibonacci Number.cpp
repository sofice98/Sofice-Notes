/**********
*DP
*Sofice
*2020/7/14
*************/
#include<bits/stdc++.h>
using namespace std;

long long dp[100];

long long fibonacci(int n) {//ֱ�ӵݹ�汾����n=40ʱ�Ѿ�����
    if (n == 0 || n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

long long fibonacci_dp(int n) {//DP�汾����n=100ʱ���ǳ���
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
        printf("��%dλ쳲�������Ϊ��%lld\n", n, fibonacci_dp(n));
    }
    

    system("pause");
    return 0;
}