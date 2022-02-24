#include <bits/stdc++.h>
#define TEST
using namespace std;
int n, m;
int G[210][210] = {};
bool isvisit[210] = {};
int mindist = INT_MAX;
int minkk;

int main(){	
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, d;
		scanf("%d %d %d", &u, &v, &d);
		G[u][v] = d;
		G[v][u] = d;
	}
	int k;
	scanf("%d", &k);
	for (int kk = 1; kk <= k;kk++) {
		memset(isvisit, 0, sizeof(bool) * 210);
		int q;
		scanf("%d", &q);
		int flag = 0;
		int *route = new int[q + 1];
		int sum = 0;
		int cnt = n;
		for (int i = 1; i <= q; i++) 
			scanf("%d", &route[i]);
		for (int i = 1; i < q; i++) {
			if (G[route[i]][route[i + 1]]) {
				sum += G[route[i]][route[i + 1]];
				if (!isvisit[route[i]]) {
					isvisit[route[i]] = true; cnt--;
				}
			}
			else {
				flag = 1; sum = -1; break;
			}
		}
		if (flag) {
			printf("Path %d: NA (Not a TS cycle)\n", kk); continue;
		}
		printf("Path %d: %d ", kk, sum);
		if (!cnt&&route[1] == route[q] && q >= n) {
			if (mindist > sum) {
				mindist = sum; minkk = kk;
			}
			if(q==n+1)	printf("(TS simple cycle)\n");
			else		printf("(TS cycle)\n");
		}
		else			printf("(Not a TS cycle)\n");
		
	}
	printf("Shortest Dist(%d) = %d", minkk, mindist);


#ifdef TEST
	system("pause");
#endif
	return 0;
}