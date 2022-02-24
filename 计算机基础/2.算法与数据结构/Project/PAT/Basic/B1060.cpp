#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int N;
	scanf("%d", &N);

	int num[100000];
	int ans = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	sort(num, num + N, [](int a, int b) { return a > b; });
	if (num[0] == 0)
		printf("0\n");
	else {
		for (int i = 0; i <= N; i++) {
			if (num[i - 1] > i) {
				ans = i;
			}
		}
		printf("%d\n", ans);
	}
	

	
#ifdef TEST
	system("pause");
#endif
	return 0;
}