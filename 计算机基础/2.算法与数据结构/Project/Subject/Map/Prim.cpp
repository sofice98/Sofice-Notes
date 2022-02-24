/**********
*最小生成树Prim算法
*Sofice
*2020/8/7
***********/
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = a;i <= b;i++)
typedef long long ll;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x7fffffff;
constexpr int MAX = 10000;
constexpr double eps = 1e-7;

struct node {
    int d, u, prev;
    node(int d,int u,int prev) :d(d), u(u), prev(prev) {}
    bool operator< (const node& b) const {
        return d > b.d;
    }
};

vector<pair<int, int>> graph[MAX];
bool vis[MAX];
int n;
int parent[MAX];
int dist[MAX];//所有顶点dist和为最小生成树权值

int Prim(int src) {
    memset(vis, 0, sizeof(vis));
    priority_queue<node> pq;
    pq.push(node(0, src, -1));
    while (!pq.empty()) {
        int u = pq.top().u;
        int d = pq.top().d;
        int prev = pq.top().prev;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        parent[u] = prev;
        dist[u] = d;
        for (auto& item : graph[u]) {
            int v = item.first;
            int w = item.second;
            if (!vis[v]) {
                pq.push(node(w, v, u));
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++) sum += dist[i];
    return sum;
}

int main() {
    int m;
    scanf("%d %d", &n, &m);
    int u, v, w;
    f(i, 1, m) {
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }
    printf("%d\n", Prim(0));
        
    return 0;
}
//7 12
//0 1 10
//0 2 3
//0 5 11
//0 4 18
//4 5 1
//1 2 5
//2 5 7
//1 3 1
//2 3 2
//3 6 2
//2 6 5
//5 6 2