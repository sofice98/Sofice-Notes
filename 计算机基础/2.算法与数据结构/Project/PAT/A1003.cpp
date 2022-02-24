#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
int w[510][510];
int numOfTeam[510];
int dist[510];
int visit[510] = {};

int main()
{
	memset(w, 0x3f, 510 * 510 * 4);
	memset(dist, 0x3f, 510 * 4);
	int n, m, c1, c2;
	scanf("%d %d %d %d", &n, &m, &c1, &c2);
	for (int i = 0; i < n; i++) 
		scanf("%d", &numOfTeam[i]);
	for (int i = 0; i < m; i++) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);
		w[a][b] = l;
		w[b][a] = l;
	}
	int pathCnt[510] = {};
	int teams[510] = {};
	pathCnt[c1] = 1;
	teams[c1] = numOfTeam[c1];
	//Dijkstra
	dist[c1] = 0;
	while (1) {
		int u, minD = INF;
		for (int i = 0; i < n; i++) {
			if (visit[i] == 0 && dist[i] < minD) {
				minD = dist[i];
				u = i;								//u=EXTRACT_MIN(Q)
			}
		}
		visit[u] = 1;								//S=S+{u}
		if (minD == INF)							//Q.size==0
			break;
		for (int v = 0; v < n; v++) {				//for each vertex v=G.Adj[u]
			if (visit[v] == 0 && w[v][u] < INF) {
				if (dist[v] > dist[u] + w[u][v]) {	//Relax(u,v,w);
					dist[v] = dist[u] + w[u][v];
					pathCnt[v] = pathCnt[u];
					teams[v] = teams[u] + numOfTeam[v];
				}
				else if (dist[v] == dist[u] + w[u][v]) {
					pathCnt[v] += pathCnt[u];
					if (teams[v] < teams[u] + numOfTeam[v])
						teams[v] = teams[u] + numOfTeam[v];
				}
			}
		}
	}
	printf("%d %d", pathCnt[c2], teams[c2]);
		

#ifdef TEST
	system("pause");
#endif
	return 0;
}