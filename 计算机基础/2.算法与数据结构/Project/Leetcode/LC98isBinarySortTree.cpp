#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
//¶þ²æÅÅÐòÊ÷ÅÐ¶Ï
bool helper(TreeNode* root, long mn, long mx) {
    if (!root) return true;
    if (root->val <= mn || root->val >= mx) return false;
    return helper(root->left, mn, root->val) && helper(root->right, root->val, mx);
}
bool isValidBST(TreeNode* root) {
    return helper(root, LONG_MIN, LONG_MAX);
}
int main()
{
	
	return 0;
}