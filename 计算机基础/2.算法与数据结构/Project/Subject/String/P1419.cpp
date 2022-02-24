/**********
*二分+前缀和
*Sofice
*2020/8/4
***********/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 100010;
int a[MAX], n, s, t;
double ans;

deque<int> hq;     //定义节点类型单调队列
double sum[MAX];

bool check(double mid) {
    hq.clear();
    sum[0] = 0;
    for (int i = 1; i <= n; i++)	sum[i] = sum[i - 1] + (double)a[i] - mid;
    
    for (int i = s; i <= n; i++) {
        while (!hq.empty() && sum[hq.back()] > sum[i - s])	hq.pop_back();
        hq.push_back(i - s);
        while (!hq.empty() && hq.front() < i - t)	hq.pop_front();
        if (!hq.empty() && sum[i] - sum[hq.front()] >= 0)	return 1;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%d %d", &s, &t);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    //二分
    double l = -10000.0, r = 10000.0;
    while (r - l >= 1e-4) {
        double mid = (l + r) / 2.0;
        if (check(mid))	ans = mid, l = mid;
        else r = mid;
    }
    printf("%.3f\n", ans);


    

    system("pause");
    return 0;
}