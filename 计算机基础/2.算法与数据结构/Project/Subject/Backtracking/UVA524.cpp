//回溯法
#include<bits/stdc++.h>
using namespace std;

bool isp[40] = {};
int res[20] = { 1 };
int n;
bool vis[20] = {};
int tot = 0;

bool is_prime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)    return false;
    }
    return true;
}

void dfs(int cur) {
    if (cur == n && isp[res[cur - 1] + 1]) {
        //输出每一个结果
        for (int i = 0; i < n - 1; i++)  printf("%d ", res[i]);
        printf("%d\n", res[n - 1]);
        tot++;
        return;
    }
    for (int i = 2; i <= n; i++) {
        if (isp[res[cur - 1] + i] && !vis[i]) {
            res[cur] = i;
            vis[i] = true;
            dfs(cur + 1);
            vis[i] = false;
        }
    }
}


int main() {
    for (int i = 2; i <= 32; i++) isp[i] = is_prime(i);
    int i = 1;
    while (scanf("%d", &n) != EOF) {
        if(i > 1)     printf("\n");
        printf("Case %d:\n", i++);
        dfs(1);
    }
    //输出总数
    //printf("%d\n", tot);
    system("pause");
    return 0;
}