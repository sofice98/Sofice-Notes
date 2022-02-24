/**********
*dp
*Sofice
*2020/10/16
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


string longestPalindrome(string s) {
    if (s.size() == 1) return s;
    int ansi,ansj;
    const int len = s.size();
    int dp[1000][1000];
    for (int k = 0; k < len; k++) {
        for (int i = 0; i < len - k; i++) {
            int j = i + k;
            if (k == 0) {
                dp[i][j] = 1;
            }
            else if (k == 1) {
                dp[i][j] = (s[i] == s[j]) ? 1 : 0;
            }
            else {
                if (dp[i + 1][j - 1] == 0) dp[i][j] = 0;
                else dp[i][j] = (s[i] == s[j]) ? 1 : 0;
            }
            if (dp[i][j]) {
                ansi = i; ansj = j;
            }
        }
    }
    return s.substr(ansi, ansj - ansi + 1);
}

int main() {
    string s("babad");
    longestPalindrome(s);

    system("pause");
    return 0;
}
