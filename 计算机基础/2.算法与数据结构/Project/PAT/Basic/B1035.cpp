#include <bits/stdc++.h>
#define TEST
using namespace std;
int n;
int a[110] = {};
int b[110] = {};

int main()
{
	
	scanf("%d", &n);
	int i, j;
	for (int i = 0; i < n; i++) 
		scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) 
		scanf("%d", &b[i]);
	for (i = n - 1; i > 0; i--) {
		if (b[i] != a[i]) 
			break;
	}
	for (j = i; j > 0; j--) {
		if (b[j] < b[j - 1])
			break;
	}
	if (j == 0) {
		printf("Insertion Sort\n");
		for (i = 1; i < n; i++) {
			if (b[i] < b[i - 1]) 
				break;
		}
		sort(b, b + i + 1);
		for (int i = 0; i < n; i++) {
			printf("%d", b[i]);
			if (i != n - 1)	putchar(' ');
		}
	}
	else {
		printf("Merge Sort\n");
		int flag = 0;
		for (int i = 2; i <= exp2((int)log2(n) + 1); i *= 2) {
			flag = equal(b, b + n, a);
			for (int j = 0; j < n / i; j++) {
				sort(a + j * i, a + j * i + i);
			}
			sort(a + n / i * i, a + n);
			if (flag) {
				for (int i = 0; i < n; i++) {
					printf("%d", a[i]);
					if (i != n - 1)	putchar(' ');
				}
			}
		}
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}