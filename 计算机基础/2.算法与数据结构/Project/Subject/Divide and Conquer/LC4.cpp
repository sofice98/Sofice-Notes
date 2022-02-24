/**********
*·ÖÖÎ
*Sofice
*2020/10/2
***********/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 10000;
constexpr double eps = 1e-7;
#define f(i, a, b) for(int i = a;i <= b;i++)


int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
    if (i >= nums1.size()) return nums2[j + k - 1];
    if (j >= nums2.size()) return nums1[i + k - 1];
    if (k == 1) return min(nums1[i], nums2[j]);
    int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
    int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
    if (midVal1 < midVal2) {
        return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
    }
    else {
        return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
    }
}

double findMedianSortedArrays(vector<int> & nums1, vector<int> & nums2) {
    int m = nums1.size();int n = nums2.size();
    return (findKth(nums1, 0, nums2, 0, (m + n + 1) / 2) + findKth(nums1, 0, nums2, 0, (m + n + 2) / 2)) / 2.0;
}

int main() {

    system("pause");
    return 0;
}
