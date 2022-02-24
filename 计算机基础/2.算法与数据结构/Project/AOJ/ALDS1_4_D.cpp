/**********
*二分
*Sofice
*2020/7/20
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAX = 100000;

int n, k;
ll T[MAX];
//计算k辆最大运载量为P的卡车能装多少货物
int check(ll P) {
    int i = 0;
    for (int truck = k; truck > 0; truck--) {
        ll sum = 0; 
        while (sum + T[i] <= P) {
            sum += T[i++];
            if (i == n)  return i;
        }
    }
    return i;
}

ll solve() {
    ll left = 0;
    ll right = MAX * 1000;
    while (left + 1 < right) {
        ll mid = left + right >> 1;
        int v = check(mid);
        if (v >= n) right = mid;
        else    left = mid;
    }
    return right;
}


int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)    scanf("%d", &T[i]);
    ll ans = solve();
    printf("%lld", ans);    

    system("pause");
    return 0;
}