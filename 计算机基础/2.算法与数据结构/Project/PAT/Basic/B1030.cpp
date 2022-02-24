#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int n, p;
	scanf("%d %d", &n, &p);

	static int num[100010];
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
	}
	sort(num, num + n);
	int ans = 1;
	for (int i = 0; i < n; i++) {
		int j = upper_bound(num + i + 1, num + n, (long long)num[i] * p) - num;
		ans = max(ans, j - i);
	}
	printf("%d", ans);


#ifdef TEST
	system("pause");
#endif
	return 0;
}