#include <bits/stdc++.h>
#define TEST
using namespace std;
int n, m;
vector<int> id[100000];

int main(){	
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		id[u].push_back(v);
		id[v].push_back(u);
	}
	while (m--) {
		int k;
		scanf("%d", &k);
		bool flag = true;
		int *query = new int[k];
		for (int i = 0; i < k; i++) {
			scanf("%d", &query[i]);
		}
		for (int i = 0; i < k; i++) {
			for (int j = i + 1; j < k; j++) {
				for(auto it=id[query[i]].begin();it!=id[query[i]].end();it++)
					if (*it == query[j]) {
						flag = false; break;
					}
				if (!flag)	break;
			}
			if (!flag)	break;
		}
		if (flag)	printf("Yes\n");
		else		printf("No\n");
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}