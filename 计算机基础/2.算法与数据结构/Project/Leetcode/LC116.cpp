#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

void helper(Node*& root) {
    if (root->left) {
        root->left->next = root->right;
        if (root->next) {
            root->right->next = root->next->left;
        }
        helper(root->left);
        helper(root->right);
    }
    return;
}

Node* connect(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    helper(root);
    return root;
}



int main()
{
    vector<vector<int>> matrix({    {1, 3},
                                    {2, 6},
                                    {8, 10} });
	
    merge(matrix);


	return 0;
}