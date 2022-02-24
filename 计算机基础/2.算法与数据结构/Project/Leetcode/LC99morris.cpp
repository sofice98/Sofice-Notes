#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//morris����
void morrisInOrderT(TreeNode* root, vector<TreeNode*>& nodes) {
    TreeNode* current = root;
    TreeNode* prev = NULL;
    TreeNode* lastNodes = new TreeNode(INT_MIN);

    while (current) {
        if (current->left == NULL) {
            if (lastNodes->val > current->val) {
                nodes.push_back(lastNodes);
                nodes.push_back(current);
            }
            lastNodes = current;
            current = current->right;
        }
        else {
            //�ҳ�ǰ��ڵ�
            prev = current->left;
            while (prev->right != NULL && prev->right != current) {
                prev = prev->right;
            }
            //�ı�ṹ
            if (prev->right == NULL) {
                prev->right = current;
                current = current->left;
            }
            else {
                // �ָ��ṹ
                prev->right = NULL;

                // ��߱������ˣ����Է����м���Ǹ���
                if (lastNodes->val > current->val) {
                    nodes.push_back(lastNodes);
                    nodes.push_back(current);
                }
                lastNodes = current;


                current = current->right;
            }
        }
    }
}

void recoverTree(TreeNode* root) {
    if (!root) return;

    vector<TreeNode*>nodes;
    morrisInOrderT(root, nodes);

    if (nodes.size() == 2) {
        int temp = nodes[0]->val;
        nodes[0]->val = nodes[1]->val;
        nodes[1]->val = temp;
    }
    else if (nodes.size() == 4) {
        int temp = nodes[0]->val;
        nodes[0]->val = nodes[3]->val;
        nodes[3]->val = temp;
    }
    return;
}
int main()
{
	
	return 0;
}