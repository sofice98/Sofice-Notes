/*************
*二分+dijkstra
*Sofice 
*2020/7/31
**************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 10010;

int n, m, b;
vector<pair<int, int>> graph[MAX];//加权邻接表
ll dist[MAX];//血量
bool vis[MAX];//访问表
int f[MAX];//过路费
int ans = -1;

//二分法控制最大的过路费最小，迪杰特斯拉算法控制血量扣得最少（因此Dijkstra里不用考虑过路费）
bool Dijkstra(int fi) {
    if (f[1] > fi) return false;
    //初始化
    fill(dist, dist + MAX, INF);
    memset(vis, 0, sizeof(vis));
    dist[1] = 0; 
    //优先级队列，pair<dist[i],i>，dist小的优先
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push(make_pair(0, 1));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (u == n) {//如果已经到达,判断是否生命值有剩余 
            if (dist[n] >= b) return false;
            else return true;
        }
        for (auto& item : graph[u]) {
            int v = item.first;
            int w = item.second;
            if (!vis[v] && dist[v] > w + dist[u] && f[v] <= fi) {//经过过路费不超过二分的fi
                dist[v] = w + dist[u];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &m, &b);
    for (int i = 1; i <= n; i++)    scanf("%d", &f[i]);
    int u, v, w;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }
    int left = 0, right = 1e9;
    while (left + 1 < right) {
        int mid = left + right >> 1;
        if (Dijkstra(mid)) {  //检查条件，如果成立
            ans = mid;
            right = mid;
        }
        else   left = mid;
    }
    if (ans == -1)   printf("AFK");
    else             printf("%d", ans);

    system("pause");
    
    return 0;
}
/*
5 7 10
8 5 6 10 3
1 2 1
1 2 2
1 3 4
2 4 1
2 5 11
3 4 3
4 5 1
*/
