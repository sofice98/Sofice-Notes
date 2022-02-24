/**********
*DP
*Sofice
*2020/7/14
*************/
#include<bits/stdc++.h>
using namespace std;

#define MAX 100
int dp[MAX][MAX];//使用前i枚硬币支付j元时所需最少枚数
int dpzip[MAX];//压缩dp
int coins[MAX];
int m, n;//m种硬币，支付n元

int solve() {//打表dp
    for (int j = 1; j <= n; j++) dp[0][j] = INT_MAX;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (j - coins[i] >= 0)
                dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i]] + 1);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[m][n];
}

int solve2() {//压缩dp矩阵至一维，减少不需要的空间,也会减少约一半时间，缺点是不能找到使用了哪几个面值的硬币
    for (int j = 1; j <= n; j++) dpzip[j] = INT_MAX;
    for (int i = 1; i <= m; i++) {
        for (int j = coins[i]; j <= n; j++) {
            dpzip[j] = min(dpzip[j], dpzip[j - coins[i]] + 1);
        }
    }
    return dpzip[n];
}

int main() {
    memset(dp, 0, sizeof(dp));
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)     scanf("%d", &coins[i]);
    while (scanf("%d", &n) != EOF) {
        printf("%d\n", solve2());
    }
    

    system("pause");
    return 0;
}