#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
int tree[110][110] = {};

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int vis[110] = {};
	queue<int> que;
	int ans[110] = {};
	int level[110] = {};
	int max_level = 0;
	memset(tree, 0x3f, sizeof(tree));
	while (m--) {
		int id, k;
		scanf("%d %d", &id, &k);
		for (int i = 0; i < k; i++) {
			int child;
			scanf("%d", &child);
			tree[id][i] = child;
		}
	}
	que.push(1);
	vis[1] = 1;
	level[1] = 1;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		int cur_level = level[u];
		if (cur_level > max_level)
			max_level = cur_level;
		int v;
		for (v = 0; 1; v++) {
			if (tree[u][v] == INF)
				break;
			if (!vis[tree[u][v]]) {
				vis[tree[u][v]] = 1;
				level[tree[u][v]] = cur_level + 1;
				que.push(tree[u][v]);
			}
		}
		if (v == 0)
			ans[cur_level]++;
	}
	for (int i = 1; i <= max_level; i++) {
		printf("%d", ans[i]);
		if (i != max_level)
			printf(" ");
	}
		


#ifdef TEST
	system("pause");
#endif
	return 0;
}