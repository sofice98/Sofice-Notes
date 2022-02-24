/**********
*分治
*Sofice
*2020/7/19
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxn = 500010;

int a[maxn], b[maxn];
ll res = 0;
//用分治思想，复杂度跟归并排序一样
void Merge(int* a, int low, int mid, int high) {
    memcpy(b + low, a + low, sizeof(int) * (high - low + 1));
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (b[i] <= b[j])  a[k++] = b[i++];
        else { 
            res += (ll)mid + 1 - i;//合并时计算有多少左边的数应该放在右边
            a[k++] = b[j++]; 
        }
    }
    while (i <= mid)   a[k++] = b[i++];
    while (j <= high)   a[k++] = b[j++];
    return;
}
void MergeSort(int* a, int low, int high) {
    if (low < high) {
        int mid = (low + high) >> 1;
        MergeSort(a, low, mid);
        MergeSort(a, mid + 1, high);
        Merge(a, low, mid, high);
    }
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)    scanf("%d", &a[i]);
    MergeSort(a, 0, n - 1);
    printf("%lld", res);

    system("pause");
    return 0;
}