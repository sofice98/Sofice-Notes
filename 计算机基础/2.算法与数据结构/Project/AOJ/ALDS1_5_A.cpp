/**********
*DP+分治
*Sofice
*2020/7/20
*选择任意几个元素加和得到目标值
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAX = 1000;
constexpr int VMAX = 2005;

int n, q;
int A[MAX];
bool dp[MAX][VMAX];
bool vis[MAX][VMAX];

//使用从第i个数及后面的数能否得到m
bool solve(int i, int m) {
    if (vis[i][m])   return dp[i][m];
    if (m == 0) { 
        vis[i][m] = true;
        return dp[i][m] = true; 
    }
    if (i >= n) {
        vis[i][m] = true;
        return false;
    }
    return solve(i + 1, m) || solve(i + 1, m - A[i]);
}


int main() {
    memset(dp, 0, sizeof(dp));
    memset(vis, 0, sizeof(vis));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)    scanf("%d", &A[i]);
    scanf("%d", &q);
    int m;
    while (q--) {
        scanf("%d", &m);
        if(solve(0, m)) printf("yes\n");
        else        printf("no\n");
    }
     

    system("pause");
    return 0;
}