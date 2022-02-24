/**************
*八皇后问题
*Sofice
*2020/7/3
***************/
#include<bits/stdc++.h>

using namespace std;

int tot = 0;
int C[8] = {};
int vis[2][8] = {};

void search(int cur) {
    if (cur == 8) {
        tot++;
        for (int i : C)  printf("%d ",i);
        printf("\n");
        return;
    }    
    for (int i = 0; i < 8; i++) {//搜索第i列
        int flag = true;
        C[cur] = i;
        for (int j = 0; j < cur; j++) {//对比已经放置的皇后
            if (i == C[j] || cur - i == j - C[j] || cur + i == j + C[j]) {
                flag = false;
            }
        }
        if (flag)    search(cur + 1);
    }
}

int main() {
    search(0);
    printf("八皇后的解的个数为：%d\n", tot);

    system("pause");
    return 0;
}