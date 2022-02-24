#include <bits/stdc++.h>
#define TEST
using namespace std;
int cmax, n, sp, m;
vector<pair<int,int>> cities[510];
int capacity[510] = {};
bool isvisited[510] = {};
int ans_send = INT_MAX, ans_back = INT_MAX, ans_dist = INT_MAX;
int send = 0, back = 0, dist = 0;
vector<int> path, ans_path;

void dfs(int u) {
	path.push_back(u);
	isvisited[u] = true;
	if (u == sp) {
		if (dist < ans_dist || (dist == ans_dist && (send < ans_send || (send == ans_send && back < ans_back)))) {
			ans_send = send;
			ans_back = back;
			ans_dist = dist;
			ans_path = path;
		}
		path.pop_back();
		isvisited[u] = false;
		return;
	}
	for (auto it = cities[u].begin(); it != cities[u].end(); it++) {
		int v = (*it).first;
		int edge = (*it).second;
		if (!isvisited[v]) {
			dist += edge;
			int tmp_send = send;
			int tmp_back = back;
			if (capacity[v] > 0) {
				send += capacity[v];
				if (send >= back) {
					send -= back;
					back = 0;
				}
				else if (send < back) {
					back -= send;
					send = 0;
				}
			}
			else if (capacity[v] < 0) {
				back -= capacity[v];
			}
			dfs(v);
			dist -= edge;
			send = tmp_send;
			back = tmp_back;
		}
	}
	path.pop_back();
	isvisited[u] = false;
}


int main()
{	
	scanf("%d %d %d %d", &cmax, &n, &sp, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &capacity[i]);
		capacity[i] = cmax / 2 - capacity[i];
	}
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		cities[a].push_back(make_pair(b, c));
		cities[b].push_back(make_pair(a, c));
	}
	dfs(0);
	printf("%d 0", ans_send);
	for (int i = 1; i < ans_path.size(); i++) 
		printf("->%d", ans_path[i]);
	printf(" %d", ans_back);
	

#ifdef TEST
	system("pause");
#endif
	return 0;
}