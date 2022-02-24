#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//morris遍历
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
            //找出前序节点
            prev = current->left;
            while (prev->right != NULL && prev->right != current) {
                prev = prev->right;
            }
            //改变结构
            if (prev->right == NULL) {
                prev->right = current;
                current = current->left;
            }
            else {
                // 恢复结构
                prev->right = NULL;

                // 左边遍历完了，可以访问中间的那个了
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