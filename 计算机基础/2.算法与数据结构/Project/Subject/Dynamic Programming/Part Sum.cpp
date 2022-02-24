/**********
*dp
*Sofice
*2020/8/6
***********/
#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b) for(int i=a;i<=b;i++)
typedef long long ll;
const int MAX = 10000;
int a[MAX], n, k;

bool dp[MAX][MAX];

int main() {
    scanf("%d %d", &n, &k);
    f(i, 0, n - 1) {
        scanf("%d", &a[i]);
    }
    dp[0][0] = true;
    f(i, 0, n) {
        f(j, 0, k) {
            for(int p = 0; p <= 1 && j - p * a[i] >= 0; p++) {
                dp[i + 1][j] |= dp[i][j - p * a[i]];
            }
        }
    }
    if (dp[n][k])    printf("Yes");
    else printf("No");
    

    system("pause");
    return 0;
}