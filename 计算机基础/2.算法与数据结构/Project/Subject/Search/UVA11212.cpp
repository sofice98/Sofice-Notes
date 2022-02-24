/**********
*IDA*
*Sofice
*2020/7/10
*************/
#include<bits/stdc++.h>
using namespace std;

int a[12];
int maxd, n, num;

int check() {//计算后继不正确的数字个数
    int diff = 0;
    for (int i = 0; i < n - 1; i++)
        if (a[i] + 1 != a[i + 1]) diff++;
    return diff;
}

bool iddfs(int cur) {
    int ret = check();
    if (!ret)   return true;
    if (3 * cur + ret > 3 * maxd)  return false;//IDA*
    bool ok = false;
    int copy[12];
    memcpy(copy, a, sizeof(a));
    //前边[i:i+j]向后，后边[i+j+1:i+j+k]向前
    for (int i = 0; i < n - 1; i++) {
        if (ok) break;
        for (int j = 0; j <= n - i - 2; j++) {
            if (ok) break;
            for (int k = 1; k <= n - i - j - 1; k++) {
                memcpy(a + i, a + i + j + 1, sizeof(int) * k);
                memcpy(a + i + k, copy + i, sizeof(int) * (j + 1));
                if (iddfs(cur + 1))  ok = true;
                memcpy(a, copy, sizeof(copy));
            }
            
        }
    }
    return ok;
}


int main() {
    while (scanf("%d", &n) && n) {
        memset(a, 0, sizeof(a));
        int ok = 0;
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (maxd = 0; maxd <= n; maxd++) {//最多移动n步
            if (iddfs(0)) {
                ok = 1;
                break;
            }
        }
        printf("Case %d: %d\n", ++num, maxd);
    }

    system("pause");
    return 0;
}