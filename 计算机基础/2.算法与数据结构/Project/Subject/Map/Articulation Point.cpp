/**********
*dp
*Sofice
*2020/8/6
***********/
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = a;i <= b;i++)
typedef long long ll;
const int MAX = 10000;
int parent[MAX],preorder[MAX],lowest[MAX];
bool vis[MAX];
int n, timer = 1;
vector<int> G[MAX];

void dfs(int u) {
    preorder[u] = lowest[u] = timer++;
    vis[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!vis[v]) {
            parent[v] = u;
            dfs(v); 
            lowest[u] = min(lowest[u], lowest[v]);
        }
        else if(u!=parent[u])
            lowest[u] = min(lowest[u], preorder[v]);
    }
}

void art_points() {
    memset(vis, 0, sizeof(vis));
    dfs(0);
    set<int> ap;
    int np;
    f(i, 1, n - 1) {
        int p = parent[i];
        if (p == 0) np++;
        else if (preorder[p] <= lowest[i]) ap.insert(p);
    }
    if (np > 1) ap.insert(0);
    for (auto it = ap.begin(); it != ap.end(); it++)
        printf("%d ", *it);
}


int main() {
    scanf("%d", &n);
    int u, v;
    f(i, 0, n - 1) {
        scanf("%d %d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    art_points();
    

    system("pause");
    return 0;
}