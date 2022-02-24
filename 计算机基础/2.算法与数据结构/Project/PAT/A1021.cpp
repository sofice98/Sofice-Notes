#include <bits/stdc++.h>
#define TEST
using namespace std;
int n;
vector<int> *G;
bool flag[10010] = {};
bool iserror = false;
int maxdepth = 0;
int nowdepth = 1;
int ans[10010];
int anscount = 0;
int k = 1;
int root;

void dfs(int u) {
	flag[u] = true;
	for (auto v = G[u].begin(); v != G[u].end(); v++) {
		nowdepth++;
		if(!flag[*v])
			dfs(*v);
		nowdepth--;
	}
	if (G[u].size() == 1) {
		if (nowdepth == maxdepth) {
			if(ans[anscount-1] != root)
				ans[anscount++] = root;
		}
		else if (nowdepth > maxdepth) {
			anscount = 0;
			maxdepth = nowdepth;
			ans[anscount++] = root;
		}
	}
}

int main()
{	
	scanf("%d", &n);
	G = new vector<int>[n + 1];
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (root = 1; root <= n; root++) {
		if (iserror) {
			if (!flag[root]) {
				dfs(root);
				k++;
			}
		}
		else {
			memset(flag, 0, sizeof(bool)*(n + 1));
			dfs(root);
		}
		if (root == 1) {
			for (int i = 1; i <= n; i++)
				if (!flag[i])
					iserror = true;
		}
	}
	if (iserror)
		printf("Error: %d components", k);
	else {
		if (n == 1)
			printf("1");
		else
			for (int i = 0; i < anscount; i++)
				printf("%d\n", ans[i]);
	}



#ifdef TEST
	system("pause");
#endif
	return 0;
}