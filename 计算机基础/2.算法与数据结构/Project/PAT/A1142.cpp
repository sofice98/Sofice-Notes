#include <bits/stdc++.h>
#define TEST
using namespace std;
int G[210][210] = {};
int nv, ne;
bool isclique(vector<int> vset) {
	for (int u = 0; u < vset.size(); u++) {
		for (int v = u + 1; v < vset.size(); v++) {
			if (!G[vset[u]][vset[v]])
				return false;
		}
	}
	return true;
}

int main()
{	
	scanf("%d %d", &nv, &ne);
	for (int i = 0; i < ne; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u][v] = 1;
		G[v][u] = 1;
	}
	int m;
	scanf("%d", &m);
	while (m--) {
		int k;
		scanf("%d", &k);
		vector<int> qr;
		for (int i = 0; i < k; i++) {
			int v;scanf("%d", &v);
			qr.push_back(v);
		}
		if (isclique(qr)) {
			for (int i = 1; i <= nv; i++) {
				bool flag = true;
				for (int j = 0; j < qr.size(); j++) 
					if (qr[j] == i || !G[i][qr[j]]) {
						flag = false; break;
					}
				if (flag) {
					printf("Not Maximal\n"); break;
				}
				else if (i == nv)
					printf("Yes\n");
			}
		}
		else 
			printf("Not a Clique\n");
			
	}



#ifdef TEST
	system("pause");
#endif
	return 0;
}