#include <bits/stdc++.h>
#define TEST
using namespace std;
struct Node {
	int data;
	int next;
};
Node node[100010];
int ans[100010];
int main()
{
	
	int first, N, K;
	int nowadr;
	int index = 0;
	scanf("%d %d %d", &first, &N, &K);
	nowadr = first;
	for (int i = 0; i < N; i++) {
		int adr, dt, nxt;
		scanf("%d %d %d", &adr, &dt, &nxt);
		node[adr].data = dt;
		node[adr].next = nxt;
	}
	for (int i = 0; nowadr != -1; i++) {
		if (node[nowadr].data < 0) {
			ans[index++] = nowadr;
		}
		nowadr = node[nowadr].next;
	}
	nowadr = first;
	for (int i = 0; nowadr != -1; i++) {
		if (node[nowadr].data >= 0 && node[nowadr].data <= K) {
			ans[index++] = nowadr;
		}
		nowadr = node[nowadr].next;
	}
	nowadr = first;
	for (int i = 0; nowadr != -1; i++) {
		if (node[nowadr].data > K) {
			ans[index++] = nowadr;
		}
		nowadr = node[nowadr].next;
	}
	for (int i = 0; i < index; i++) {
		if(i != index - 1)
			printf("%05d %d %05d\n", ans[i], node[ans[i]].data, ans[i + 1]);
		else
			printf("%05d %d -1\n", ans[i], node[ans[i]].data);
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}
