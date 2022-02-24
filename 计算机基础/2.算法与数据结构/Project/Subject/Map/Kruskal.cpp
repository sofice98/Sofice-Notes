/**********
*最小生成树Kruskal算法
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

struct DisjointSet {
    vector<int> rank, p;//高度，父指针
    DisjointSet() {}
    DisjointSet(int size) {
        rank.resize(size, 0);
        p.resize(size, 0);
        for (int i = 0; i < size; i++)     makeSet(i);
    }
    //建立
    void makeSet(int x) {
        p[x] = x;
        rank[x] = 0;
    }
    //合并
    void unite(int x, int y) {
        int xp = findSet(x);
        int yp = findSet(y);
        if (rank[xp] > rank[yp])  p[yp] = xp;
        else {
            p[xp] = yp;
            if (rank[xp] == rank[yp])    rank[yp]++;
        }
    }
    //查找
    int findSet(int x) {
        if (x != p[x]) {
            p[x] = findSet(p[x]);
        }
        return p[x];
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }
};

struct Edge {
    int u, v, w;
    Edge(int u = 0,int v = 0,int w = 0) :
        u(u), v(v), w(w) {}
    bool operator< (const Edge& e) const {
        return w < e.w;
    }
};

vector<Edge> edges;
int n;

int Kruskal() {
    int totalCost = 0;
    sort(edges.begin(), edges.end());
    DisjointSet dset = DisjointSet(n + 1);
    int u, v;
    for (auto& e : edges) {
        if (!dset.same(e.u, e.v)) {
            totalCost += e.w;
            dset.unite(e.u, e.v);
        }
    }
    return totalCost;
}

int main() {
    int m, u, v, w;
    scanf("%d %d", &n, &m);
    f(i, 1, m) {
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(Edge(u, v, w));
    }
    printf("%d\n", Kruskal());
        
    system("pause");
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