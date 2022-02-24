#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
int w[510][510] = {};
int cost[510][510] = {};
int dist[510] = {};
int costcnt[510] = {};
int parent[510] = {};
int vis[510] = {};
void print(int i, int s) {
	if (i == s) {
		printf("%d ", s);
		return;
	}
	print(parent[i], s);
	printf("%d ", i);
	return;
}

int main()
{
	int n, m, s, d;
	scanf("%d %d %d %d", &n, &m, &s, &d);
	memset(dist, 0x3f, sizeof(dist));
	memset(w, 0x3f, sizeof(w));
	memset(cost, 0x3f, sizeof(cost));
	memset(costcnt, 0x3f, sizeof(costcnt));
	for (int i = 0; i < m; i++) {
		int u, v, d, c;
		scanf("%d %d %d %d", &u, &v, &d, &c);
		w[u][v] = d;
		w[v][u] = d;
		cost[u][v] = c;
		cost[v][u] = c;
	}
	dist[s] = 0;
	costcnt[s] = 0;
	while (1) {
		int u, minD = INF;
		for (int i = 0; i < n; i++) {
			if (dist[i] < minD && !vis[i]) {
				minD = dist[i];
				u = i;
			}
		}
		if (minD == INF)
			break;
		vis[u] = 1;
		for (int v = 0; v < n; v++) {
			if (v != u && w[u][v] != INF) {
				if (dist[v] > dist[u] + w[u][v]) {
					dist[v] = dist[u] + w[u][v];
					costcnt[v] = costcnt[u] + cost[u][v];
					parent[v] = u;
				}
				else if (dist[v] == dist[u] + w[u][v]) {
					if (costcnt[v] > costcnt[u] + cost[u][v]) {
						costcnt[v] = costcnt[u] + cost[u][v];
						parent[v] = u;
					}
				}
			}
		}
	}
	print(d, s);
	printf("%d %d", dist[d], costcnt[d]);


#ifdef TEST
	system("pause");
#endif
	return 0;
}