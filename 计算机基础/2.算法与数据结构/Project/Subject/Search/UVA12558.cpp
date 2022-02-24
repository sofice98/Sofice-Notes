/******
*������������
*sofice
*2020/7/7
********/
#include<bits/stdc++.h>
using namespace std;
#define LL long long

int maxd;
LL ans[500];
LL v[500];

int gcd(LL a, LL b) {
    return a % b == 0 ? b : gcd(b, a % b);
}
//�������1 / c <= aa / bb����Сc
int get_first(LL aa, LL bb) {
    for (int c = 2;; c++) {
        if (1.0 / c <= (float)aa / bb)
            return c;
    }
}
//�����ǰ��v���ţ�����ans
bool better(int d) {
    for (int i = d; i >= 0; i--) {
        if (v[i] != ans[i]) 
            return ans[i] == -1 || v[i] < ans[i];
    }
    return false;
}
//��ǰ���Ϊd����Ĺ����С��from������֮��Ϊaa/bb
bool dfs(int d, int from, LL aa, LL bb) {
    if (d == maxd) {
        if (bb % aa) return false;//û�ҵ���
        v[d] = bb / aa;
        if (better(d))   memcpy(ans, v, sizeof(LL) * (d + 1));
        return true;
    }
    bool ok = false;
    from = max(from, get_first(aa, bb));
    for (int i = from;; i++) {
        //��֦
        if (bb * (maxd + 1 - d) <= i * aa) break;
        v[d] = i;
        //����aa/bb - 1/i��Լ��
        LL b2 = bb * i;
        LL a2 = aa * i - bb;
        if (a2 < 0 || b2 < 0)    break;
        LL g = gcd(b2, a2);
        if (dfs(d + 1, i + 1, a2 / g, b2 / g))  ok = true;
    }
    return ok;
}

int main() {
    int ok = 0;
    int a, b;
    scanf("%d %d", &a, &b);
    for (maxd = 1;; maxd++) {//��������
        memset(ans, -1, sizeof(ans));
        if (dfs(0, get_first(a, b), a, b)) {
            ok = 1; break;
        }
    }
    printf("%d/%d=", a, b);
    for (int i = 0; ans[i] != -1; i++) {
        if(i==0)    printf("1/%lld", ans[i]);
        else        printf("+1/%lld", ans[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}