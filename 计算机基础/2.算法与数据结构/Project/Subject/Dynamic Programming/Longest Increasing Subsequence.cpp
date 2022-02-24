/**********
*DP+二分
*Sofice
*2020/7/15
*************/
#include<bits/stdc++.h>
using namespace std;

#define MAX 100000
int dp[MAX];
int a[MAX], p[MAX];
int n;
int finalLIS[MAX];

int LIS() {//时间复杂度n2，
    memset(dp, 0, sizeof(dp));
    memset(p, 0, sizeof(p));
    a[0] = -1; dp[0] = 0; p[0] = -1;
    for (int i = 1; i <= n; i++) {//计算以a[i]为结尾的LIS长度
        int k = 0;
        for (int j = 0; j <= i - 1; j++) {
            if (a[i] > a[j] && dp[j] > dp[k])  k = j;
        }
        dp[i] = dp[k] + 1;//满足a[j]<a[i]且dp[j]最大的j
        p[i] = k;//存储父节点
    }
    int res = 0;
    for (int i = 1; i <= n; i++)   if (dp[res] < dp[i])  res = i;//找dp最大值
    return res;//返回LIS的最后一个字符下标
}

int LIS_up() {//加入二分搜索,时间复杂度nlogn,
    memset(dp, 0, sizeof(dp));//长度为i+1的IS末尾元素最小值，dp是非减数组    
    int length = 0;//前i个元素构成的LIS长度-1，dp数组尾指针
    dp[0] = a[1];
    for (int i = 2; i <= n; i++) {
        if (dp[length] < a[i]) {
            dp[++length] = a[i];
            memcpy(finalLIS, dp, sizeof(int) * (length + 1));//储存LIS
        }
        else //二分搜索找到大于a[i]的最小dp，替换
            *lower_bound(dp, dp + length + 1, a[i]) = a[i];
    }
    return length + 1;
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)     scanf("%d", &a[i]);
    printf("%d\n", LIS_up());
    

    system("pause");
    return 0;
}