/**********
*���ݹ�
*Sofice
*2020/7/21
*�������������������������������
*************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

typedef struct Node {
    int value;
    Node *left, *right;
    Node(int v = 0) :value(v), left(nullptr), right(nullptr) {}
}BTree;

vector<int> pre, in, post;
int n;
//����pre�����䣬ȷ���������������䣬����������
Node* construction(int pl, int pr, int il, int ir) {
    if (pl > pr) return nullptr;
    int vroot = pre[pl];//����ֵ
    int j = find(in.begin() + il, in.end() - n + ir + 1, vroot) - in.begin();//in�и����±�
    Node* root = new Node(vroot);//������
    root->left = construction(pl + 1, pl + j - il, il, j - 1);
    root->right = construction(pl + j - il + 1, pr, j + 1, ir);
    return root;
}

void postPrint(Node *root) {
    if (root) {
        postPrint(root->left);
        postPrint(root->right);
        printf("%d ", root->value);
    }
}

int main() {
    scanf("%d", &n);
    int k;
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        pre.push_back(k);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        in.push_back(k);
    }
    Node* root = construction(0, n - 1, 0, n - 1);
    postPrint(root);

    system("pause");
    return 0;
}