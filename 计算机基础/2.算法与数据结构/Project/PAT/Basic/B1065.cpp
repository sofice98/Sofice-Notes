#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int N;
	scanf("%d", &N);
	int M;
	static bool flag[100010] = {};
	static int num[100010] = {};
	static int couple[100010] = {};
	static int check[100010] = {};
	vector<int> ans;
	for (int i = 0; i < 100010; i++) {
		couple[i] = 100000;
	}
	for (int i = 0,a = 0,b = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		num[a] = a; couple[a] = b;
		num[b] = b; couple[b] = a;
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", &check[i]);
	}
	sort(check, check + M);
	for (int i = 0; i < M; i++) {
		flag[check[i]] = true;
	}
	for (int i = 0; i < M; i++) {
		if (couple[check[i]] == 100000) {
			ans.push_back(check[i]);
		}
		else if (flag[check[i]] ^ flag[couple[check[i]]]) {
			ans.push_back(check[i]);
			flag[check[i]] = flag[couple[check[i]]] = true;
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf("%05d", ans[i]);
		if(i!= ans.size()-1)
			printf(" ");
	}

	
#ifdef TEST
	system("pause");
#endif
	return 0;
}