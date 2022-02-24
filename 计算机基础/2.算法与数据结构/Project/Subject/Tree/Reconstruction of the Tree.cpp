/**********
*树递归
*Sofice
*2020/7/21
*给定二叉树先序，中序遍历，求后序遍历
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
//给定pre的区间，确定根，左子树区间，右子树区间
Node* construction(int pl, int pr, int il, int ir) {
    if (pl > pr) return nullptr;
    int vroot = pre[pl];//根的值
    int j = find(in.begin() + il, in.end() - n + ir + 1, vroot) - in.begin();//in中根的下标
    Node* root = new Node(vroot);//创建根
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