#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
queue<int> lines[20];
int n, m, k, q;
int times[20] = {};
int ans[1010] = {};
int *ptime;

int outLine() {
	int min = INF;
	int index = -1;
	for (int i = 0; i < n; i++) {
		if (!lines[i].empty() && min > ptime[lines[i].front()] + times[i]) {
			min = ptime[lines[i].front()] + times[i];
			index = i;
		}
	}
	times[index] = min;
	ans[lines[index].front()] = min;
	lines[index].pop();
	return index;
}


int main()
{
	int whichline = 0;
	scanf("%d %d %d %d", &n, &m, &k, &q);
	int count = k;
	ptime = new int[k + 1]{};
	for (int i = 1; i <= k; i++) {
		scanf("%d", &ptime[i]);
	}
	for (int i = 1; i <= n*m && i <= k; i++) {
		lines[whichline++%n].push(i);
	}
	for (int i = n*m + 1; i <= k; i++) {
		whichline = outLine();
		count--;
		lines[whichline].push(i);
	}
	while (count--) {
		outLine();
	}
	for (int i = 1; i <= q; i++) {
		int query;
		scanf("%d", &query);
		int t = ans[query];
		if (t - ptime[query] >= 540)
			printf("Sorry");
		else {
			int h = 8 + t / 60;
			t -= t / 60 * 60;
			printf("%02d:%02d", h, t);
		}
		if (i != q)	printf("\n");
	}

	

#ifdef TEST
	system("pause");
#endif
	return 0;
}