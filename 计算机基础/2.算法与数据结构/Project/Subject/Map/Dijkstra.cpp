/*************
*单源最短路径
*Sofice 
*2020/7/29
**************/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 1000;

int n;
vector<pair<int, int>> graph[MAX];//加权邻接表
int dist[MAX];//距离表
bool vis[MAX];//访问表
int f[MAX];//父节点

//迪杰斯特拉算法+优先级队列，Tn=o((V+E)logV)
void Dijkstra(int src) {
    //初始化
    fill(dist, dist + MAX, INF);
    memset(vis, 0, sizeof(vis));
    dist[src] = 0; f[src] = -1;
    //优先级队列，pair<dist[i],i>，dist小的优先
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto& item : graph[u]) {
            int v = item.first;
            int w = item.second;
            if (!vis[v] && dist[v] > d + w) {
                dist[v] = d + w;
                pq.push(make_pair(dist[v], v));
                f[v] = u;
            }
        }
    }
}
//递归输出单源最短路径
void printPath(int src, int dest) {
    if (dest == -1)  return;
    printPath(src, f[dest]);
    printf("%d ", dest);
}

int main() {
    cin >> n;
    int u, v, w;
    while (1) {
        cin >> u >> v >> w;
        if (u == -1)   break;
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }
    Dijkstra(0);
    printPath(0, 4);

    system("pause");
    
    return 0;
}
/*
7
0 1 10
0 2 3
0 5 11
0 4 18
4 5 1
1 2 5
2 5 7
1 3 1
2 3 2
2 6 5
3 6 2
5 6 2
-1 -1 -1
*/
