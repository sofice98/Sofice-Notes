#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int mod = 1e9 + 7;
constexpr int maxv = 1000;

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





int main() {



    return 0;
}
