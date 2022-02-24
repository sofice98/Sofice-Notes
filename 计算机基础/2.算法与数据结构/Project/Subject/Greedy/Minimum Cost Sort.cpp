/**********
*������̰��
*Sofice
*2020/7/20
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int MAX = 1000;
constexpr int VMAX = 10000;

int n, A[MAX], s;
int B[MAX], T[VMAX + 1];

//��ÿ������Ԫ��ָ������λ�ã�����γ����ɸ�Բ
//����Ϊ1��Բ�����ƶ����ɱ�Ϊ0������Ϊ2��Բֻ��һ�ν������ɱ�Ϊ���ߺ�
//���ȴ���2��Բ�����ֿ��ܣ�
//1.����Ԫ�أ�ʹ��Բ����СֵԪ��������Ԫ�طֱ𽻻�n-1�Σ��ܳɱ���Բ��Ԫ�غ�+(n-2)*Բ����Сֵ
//2.��������СԪ�أ����ӵĳɱ�Ϊ��2*(Բ����СԪ��+���Ԫ��)����Լ�ɱ���(n-1)*(Բ����СԪ��-���Ԫ��)��
//                  �ܳɱ���Բ��Ԫ�غ�+Բ����СԪ��+(n+1)*���Ԫ��
//ȡ���߽�С��һ��
//ʱ�临�Ӷ�Ϊnlogn��ȡ����sort
int solve() {
    int ans = 0;
    bool V[MAX];//��������
    for (int i = 0; i < n; i++) {
        B[i] = A[i];
        V[i] = false;
    }
    sort(B, B + n);//B����A����
    for (int i = 0; i < n; i++)    T[B[i]] = i;//ָ������
    for (int i = 0; i < n; i++) {//ȷ������Ԫ�ط��ʵ�
        if (V[i])    continue;
        int cur = i;//��ǰ����Ԫ��
        int S = 0;//Բ����֮��
        int m = VMAX;//Բ����С��
        int an = 0;//Բ��Ԫ����
        while (1) {
            V[cur] = true;
            an++;
            int v = A[cur];
            m = min(m, v);
            S += v;
            cur = T[v];
            if (V[cur])  break;
        }
        ans += min(S + (an - 2) * m, S + m + (an + 1) * s);
    }
    return ans;
}


int main() {
    scanf("%d", &n);
    s = VMAX;
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]); 
        s = min(s, A[i]);//����Ԫ����Сֵ
    }
    int ans = solve();
    printf("%d", ans);

    system("pause");
    return 0;
}