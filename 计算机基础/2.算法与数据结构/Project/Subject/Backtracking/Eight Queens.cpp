/**************
*�˻ʺ�����
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
    for (int i = 0; i < 8; i++) {//������i��
        int flag = true;
        C[cur] = i;
        for (int j = 0; j < cur; j++) {//�Ա��Ѿ����õĻʺ�
            if (i == C[j] || cur - i == j - C[j] || cur + i == j + C[j]) {
                flag = false;
            }
        }
        if (flag)    search(cur + 1);
    }
}

int main() {
    search(0);
    printf("�˻ʺ�Ľ�ĸ���Ϊ��%d\n", tot);

    system("pause");
    return 0;
}