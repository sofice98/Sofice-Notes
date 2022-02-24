#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1e9 + 7;
constexpr int maxv = 1000;

int G[maxv][maxv];
bool vis[maxv];
int n;
//bfs
void bfs(int cur) {
    queue<int> q;
    q.push(cur);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        vis[i] = true;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && G[i][j])    q.push(j);
        }
    }

}
void bfsTraverse() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i])     bfs(i);
    }
}
//dfs
void dfs(int cur) {
    vis[cur] = true;
    for (int j = 0; j < n; j++) {
        if (!vis[j] && G[cur][j])    dfs(j);
    }
}
void dfsTraverse() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        if (!vis[i])     dfs(i);
    }
}

int main() {
    
    
    
    return 0;
}
