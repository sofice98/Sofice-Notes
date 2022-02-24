#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1e9 + 7;

int test;
int n, m;
int dp[1001][1001][11];//���ǵ���i�����Ѿ�����j����������i��ǰ����k��


int main() {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= 1000; i++) dp[i][0][0] = 1;
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= 10; k++) {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % mod;
                if (k < 10) {
                    ll x = (ll)dp[i - 1][j - 1][k] * (i - 1) % mod;
                    dp[i][j][k + 1] = (dp[i][j][k + 1] + x) % mod;
                }
            }
        }
    }
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &m);
        printf("%d\n", (dp[n][m][0])? dp[n][m][0] : -1);
    }
    
    
    return 0;
}
