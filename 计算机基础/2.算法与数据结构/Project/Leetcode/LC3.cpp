/**********
*»¬¶¯´°¿Ú£¬dp
*Sofice
*2020/10/2
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


int lengthOfLongestSubstring(string s) {
    if (s.length() == 0)  return 0;
    set<char> subset;
    int ans = 0;
    auto it = s.begin();
    for (auto c = s.begin(); c != s.end(); c++) {
        if (subset.count(*c)) {
            for (auto tmp = it; tmp != c; tmp++) {
                if (*tmp != *c) 
                    subset.erase(*tmp);
                else {
                    it = tmp + 1;break;
                }
            }
        }
        else {
            subset.insert(*c);
        }
        ans = max(ans, (int)subset.size());
    }
    return ans;
}

int main() {

    system("pause");
    return 0;
}
