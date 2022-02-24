/**********
*DP
*Sofice
*2020/7/10
*************/
#include<bits/stdc++.h>
using namespace std;
constexpr auto MAX = 101;
int n, W;
int w[MAX], v[MAX];//[1...n]
int dp[MAX];//滚动数组，d[i][j]:从第1个到第i个物品选出最优的不超过j的解

int solve(){
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i<= n; i++) {
        for (int j = W; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);//分别为不选和选
        }
    }
    return dp[W];
}

int main() {
    memset(w, 0, sizeof(w));
    memset(v, 0, sizeof(v));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d %d", &w[i], &v[i]);
    scanf("%d", &W);
    printf("%d", solve());
    


    system("pause");
    return 0;
}