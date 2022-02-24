#include <bits/stdc++.h>
#define TEST
using namespace std;
struct node {
	int adress;
	int data;
	int next;
};

int main()
{
	int last_next, n, k;
	scanf("%d %d %d", &last_next, &n, &k);
	if (!n)	last_next = -1;

	static node nodes[100010];
	static node* output[100010];
	int j = k;
	for (int i = 0; i < n; i++) {
		int tmp;
		scanf("%d", &tmp); nodes[tmp].adress = tmp;
		scanf("%d %d", &nodes[tmp].data, &nodes[tmp].next);
	}
	for (int i = 0; i < n; i++) {
		node* tmp = &nodes[last_next];
		output[i] = tmp;
		last_next = tmp->next;
		if (last_next == -1) {
			n = i + 1;
			break;
		}
	}
	for (int i = n, j = 0; i >= k; i -= k, j += k) {
			reverse(output + j, output + j + k);
	}
	for (int i = 0; i < n; i++) {
		if (i == n - 1)	printf("%05d %d %d\n", output[i]->adress, output[i]->data, -1);
		else printf("%05d %d %05d\n", output[i]->adress, output[i]->data, output[i + 1]->adress);
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}