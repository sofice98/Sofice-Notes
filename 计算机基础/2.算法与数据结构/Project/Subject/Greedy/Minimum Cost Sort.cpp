/**********
*搜索，贪心
*Sofice
*2020/7/20
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int MAX = 1000;
constexpr int VMAX = 10000;

int n, A[MAX], s;
int B[MAX], T[VMAX + 1];

//将每个待排元素指向最终位置，则会形成若干个圆
//长度为1的圆不用移动，成本为0；长度为2的圆只需一次交换，成本为二者和
//长度大于2的圆有两种可能：
//1.不借元素：使用圆内最小值元素与其他元素分别交换n-1次，总成本：圆内元素和+(n-2)*圆内最小值
//2.借整体最小元素：增加的成本为：2*(圆内最小元素+借的元素)，节约成本：(n-1)*(圆内最小元素-借的元素)，
//                  总成本：圆内元素和+圆内最小元素+(n+1)*借的元素
//取两者较小的一方
//时间复杂度为nlogn，取决于sort
int solve() {
    int ans = 0;
    bool V[MAX];//访问数组
    for (int i = 0; i < n; i++) {
        B[i] = A[i];
        V[i] = false;
    }
    sort(B, B + n);//B有序A无序
    for (int i = 0; i < n; i++)    T[B[i]] = i;//指针数组
    for (int i = 0; i < n; i++) {//确保所有元素访问到
        if (V[i])    continue;
        int cur = i;//当前处理元素
        int S = 0;//圆内数之和
        int m = VMAX;//圆内最小数
        int an = 0;//圆内元素数
        while (1) {
            V[cur] = true;
            an++;
            int v = A[cur];
            m = min(m, v);
            S += v;
            cur = T[v];
            if (V[cur])  break;
        }
        ans += min(S + (an - 2) * m, S + m + (an + 1) * s);
    }
    return ans;
}


int main() {
    scanf("%d", &n);
    s = VMAX;
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]); 
        s = min(s, A[i]);//整体元素最小值
    }
    int ans = solve();
    printf("%d", ans);

    system("pause");
    return 0;
}