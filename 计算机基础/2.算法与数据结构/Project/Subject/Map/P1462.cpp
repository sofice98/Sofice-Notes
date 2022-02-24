/*************
*����+dijkstra
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
vector<pair<int, int>> graph[MAX];//��Ȩ�ڽӱ�
ll dist[MAX];//Ѫ��
bool vis[MAX];//���ʱ�
int f[MAX];//��·��
int ans = -1;

//���ַ��������Ĺ�·����С���Ͻ���˹���㷨����Ѫ���۵����٣����Dijkstra�ﲻ�ÿ��ǹ�·�ѣ�
bool Dijkstra(int fi) {
    if (f[1] > fi) return false;
    //��ʼ��
    fill(dist, dist + MAX, INF);
    memset(vis, 0, sizeof(vis));
    dist[1] = 0; 
    //���ȼ����У�pair<dist[i],i>��distС������
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push(make_pair(0, 1));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        if (u == n) {//����Ѿ�����,�ж��Ƿ�����ֵ��ʣ�� 
            if (dist[n] >= b) return false;
            else return true;
        }
        for (auto& item : graph[u]) {
            int v = item.first;
            int w = item.second;
            if (!vis[v] && dist[v] > w + dist[u] && f[v] <= fi) {//������·�Ѳ��������ֵ�fi
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
        if (Dijkstra(mid)) {  //����������������
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
