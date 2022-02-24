#include <bits/stdc++.h>
#define TEST
using namespace std;
int n;
int postorder[40] = {};
int inorder[40] = {};
int preorder[100010] = {};
void fun(int post_p, int post_q, int in_p, int in_q, int pre) {
	if (post_p > post_q || in_p > in_q)
		return;
	int root = postorder[post_q];
	int root_index;
	for (int i = in_p; i <= in_q; i++)
		if (inorder[i] == root) {
			root_index = i; break;
		}
	preorder[pre] = root;
	fun(post_p, post_p + root_index - in_p - 1, in_p, root_index - 1, pre * 2);
	fun(post_q - in_q + root_index, post_q - 1, root_index + 1, in_q, pre * 2 + 1);
}


int main()
{	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &postorder[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &inorder[i]);
	fun(1, n, 1, n, 1);
	printf("%d", preorder[1]); n--;
	for (int i = 2; i <= 100000; i++) {
		if (preorder[i] != 0) {
			printf(" %d", preorder[i]);
			if (--n == 0)
				break;
		}
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}