#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int k, sum = 0;
	scanf("%d", &k);
	double hash[1010] = {};
	for (int i = 0; i < k; i++) {
		int n; double a;
		scanf("%d %lf", &n, &a);
		hash[n] += a;
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int n; double a;
		scanf("%d %lf", &n, &a);
		hash[n] += a;
	}
	for (int i = 1000; i >= 0; i--) {
		if (hash[i] != 0)
			sum++;
	}
	printf("%d", sum);
	for (int i = 1000; i >= 0; i--) {
		if (hash[i] != 0) {
			printf(" %d %.1lf", i, hash[i]);
		}
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}