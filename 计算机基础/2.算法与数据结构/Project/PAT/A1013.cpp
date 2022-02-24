#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
vector<int> *cities;
bool flag[1010] = {};
int x, ans;
void dfs(int i) {
	for (auto every : cities[i]) {
		if (every != x && !flag[every]) {
			flag[every] = true; 
			dfs(every);

		}
	}
}
int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	cities = new vector<int>[n + 1];
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		cities[a].push_back(b);
		cities[b].push_back(a);
	}
	while (k--) {
		memset(flag, 0, sizeof(flag));
		ans = 0;
		scanf("%d", &x);
		flag[x] = true;
		for (int i = 1; i <= n; i++) {
			if (i != x&&!flag[i]) {
				ans++;
				flag[i] = true;
				dfs(i);
			}
		}
		printf("%d\n", ans - 1);
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}
