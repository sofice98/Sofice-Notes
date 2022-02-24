#include <bits/stdc++.h>
#define TEST
using namespace std;
int m, n;
int u, v;
struct node {
	int data;
	int l = -1;
	int r = -1;
};
node *bst;

void build(int l,int r) {
	if (l == r) {
		return;
	}
	int i;
	for (i = l + 1; i <= r; i++) {
		if (bst[i].data >= bst[l].data)
			break;
	}
	if (i > r) {
		bst[l].l = l + 1;
		build(l + 1, i - 1);
		return;
	}
	if (i == l + 1) {
		bst[l].r = i;
		build(i, r);
		return;
	}
	bst[l].l = l + 1;
	bst[l].r = i;
	build(l + 1, i - 1);
	build(i, r);
}
int lca(int root) {
	if (u < bst[root].data && v < bst[root].data)
		return lca(bst[root].l);
	if (u > bst[root].data && v > bst[root].data)
		return lca(bst[root].r);
	if ((u <= bst[root].data && v >= bst[root].data) || (u >= bst[root].data && v <= bst[root].data))
		return root;
}
bool find(int x, int root) {
	if (root == -1)
		return false;
	if (bst[root].data == x)
		return true;
	if(x < bst[root].data)
		find(x, bst[root].l);
	else 
		find(x, bst[root].r);
}


int main(){	
	scanf("%d %d", &m, &n);
	bst = new node[10010];
	for (int i = 1; i <= n; i++) 
		scanf("%d", &bst[i].data);
	build(1, n);
	while (m--) {
		scanf("%d %d", &u, &v);
		if (!find(u, 1)) {
			if (!find(v, 1))
				printf("ERROR: %d and %d are not found.\n", u, v);
			else
				printf("ERROR: %d is not found.\n", u);
		}
		else {
			if (!find(v, 1))
				printf("ERROR: %d is not found.\n", v);
			else {
				int l = bst[lca(1)].data;
				if(l == u)
					printf("%d is an ancestor of %d.\n", u, v);
				else if (l == v)
					printf("%d is an ancestor of %d.\n", v, u);
				else
					printf("LCA of %d and %d is %d.\n", u, v, l);
			}
		}
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}