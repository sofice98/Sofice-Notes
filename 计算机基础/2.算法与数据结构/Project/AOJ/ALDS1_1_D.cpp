/**********
*DP
*Sofice
*2020/7/15
*************/
#include<bits/stdc++.h>
using namespace std;
int n, a;
int maxv = INT_MIN, minv;

int main() {
    scanf("%d", &n);  
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        if (i == 0)    minv = a;
        if (i > 0) {
            maxv = max(maxv, a - minv);
            minv = min(minv, a);
        }
    }
    printf("%d", maxv);
    

    system("pause");
    return 0;
}