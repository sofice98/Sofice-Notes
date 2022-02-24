#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
//·ÖÖÎ
vector<TreeNode*> helper(int start, int end) {
    if (start > end)   return { nullptr };
    vector<TreeNode*> res;
    for (int i = start; i <= end; i++) {
        auto left = helper(start, i - 1);
        auto right = helper(i + 1, end);
        for (auto l : left) {
            for (auto r : right) {
                TreeNode* tmp = new TreeNode(i);
                tmp->left = l;
                tmp->right = r;
                res.push_back(tmp);
            }
        }
    }
    return res;
}

vector<TreeNode*> generateTrees(int n) {
    if (n <= 0)  return {};
    return helper(1, n);
}

//DP
//vector<TreeNode*> generateTrees(int n) {
//    if (n == 0) return {};
//    vector<vector<vector<TreeNode*>>> memo(n, vector<vector<TreeNode*>>(n));
//    return helper(1, n, memo);
//}
//vector<TreeNode*> helper(int start, int end, vector<vector<vector<TreeNode*>>>& memo) {
//    if (start > end) return { nullptr };
//    if (!memo[start - 1][end - 1].empty()) return memo[start - 1][end - 1];
//    vector<TreeNode*> res;
//    for (int i = start; i <= end; ++i) {
//        auto left = helper(start, i - 1, memo), right = helper(i + 1, end, memo);
//        for (auto a : left) {
//            for (auto b : right) {
//                TreeNode* node = new TreeNode(i);
//                node->left = a;
//                node->right = b;
//                res.push_back(node);
//            }
//        }
//    }
//    return memo[start - 1][end - 1] = res;
//}

int main()
{
    generateTrees(3);
	
	return 0;
}