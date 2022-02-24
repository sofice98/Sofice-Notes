/**********
*DP
*Sofice
*2020/7/14
*************/
#include<bits/stdc++.h>
using namespace std;

#define MAX 100
int dp[MAX][MAX];//mi...mj��������˷���С����
int p[MAX];

void fun(int n) {//����m1...mn
    for (int l = 2; l <= n; l++) {//�����������
        for (int i = 1; i <= n - l + 1; i++) {//�ֱ����mi...mj����Ϊl�Ĺ�n-l-1��
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {//ÿ������kΪ�ֽ�����������Ž�
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; i++)   scanf("%d", &p[i]);
    fun(n);
    printf("%d\n", dp[1][n]);
    
    
    

    system("pause");
    return 0;
}