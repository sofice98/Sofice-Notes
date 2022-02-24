#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    vector<int> tmp;
    queue<TreeNode*> q;
    if (!root)   return res;
    q.push(root);
    while (!q.empty()) {
        
    }
}
int main()
{
	
	return 0;
}