/**********
*DP
*Sofice
*2020/7/14
*************/
#include<bits/stdc++.h>
using namespace std;

#define MAX 1000
int dp[MAX][MAX];
string x, y;

void lcs() {
    int m = x.length();
    int n = y.length();
    for (int i = 1; i <= m; i++) {//´ò±í
        for (int j = 1; j <= n; j++) {
            if (x[i] == y[j]) 
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else 
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        memset(dp, 0, sizeof(dp));
        cin >> x >> y;
        lcs();
        printf("%d\n", dp[x.length()][y.length()]);
    }
    
    
    

    system("pause");
    return 0;
}