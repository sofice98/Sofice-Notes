/**********
*DP+����
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

int LIS() {//ʱ�临�Ӷ�n2��
    memset(dp, 0, sizeof(dp));
    memset(p, 0, sizeof(p));
    a[0] = -1; dp[0] = 0; p[0] = -1;
    for (int i = 1; i <= n; i++) {//������a[i]Ϊ��β��LIS����
        int k = 0;
        for (int j = 0; j <= i - 1; j++) {
            if (a[i] > a[j] && dp[j] > dp[k])  k = j;
        }
        dp[i] = dp[k] + 1;//����a[j]<a[i]��dp[j]����j
        p[i] = k;//�洢���ڵ�
    }
    int res = 0;
    for (int i = 1; i <= n; i++)   if (dp[res] < dp[i])  res = i;//��dp���ֵ
    return res;//����LIS�����һ���ַ��±�
}

int LIS_up() {//�����������,ʱ�临�Ӷ�nlogn,
    memset(dp, 0, sizeof(dp));//����Ϊi+1��ISĩβԪ����Сֵ��dp�ǷǼ�����    
    int length = 0;//ǰi��Ԫ�ع��ɵ�LIS����-1��dp����βָ��
    dp[0] = a[1];
    for (int i = 2; i <= n; i++) {
        if (dp[length] < a[i]) {
            dp[++length] = a[i];
            memcpy(finalLIS, dp, sizeof(int) * (length + 1));//����LIS
        }
        else //���������ҵ�����a[i]����Сdp���滻
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