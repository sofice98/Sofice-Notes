#include <bits/stdc++.h>
#define TEST
using namespace std;
int** matrix;
int num[10010] = {};

int main()
{
	int N;
	scanf("%d", &N);
	int m, n, dire = 0;
	for (int i = sqrt(N); i > 0; i--) {
		if (N%i == 0) {
			n = i; m = N / i; break;
		}
	}
	matrix = new int*[m + 1];
	for (int i = 0; i < m + 1; i++)
		matrix[i] = new int[n + 1];
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	sort(num, num + N, [](int a, int b) { return a > b; });
	for (int k = 0, i = 0, j = 0; k < N; k++) {
		if (dire % 4 == 0) {
			matrix[i][j] = num[k];
			if (j == n - 1 - dire / 4) {
				dire++; i++;
			}
			else
				j++;
		}
		else if (dire % 4 == 1) {
			matrix[i][j] = num[k];
			if (i == m - 1 - dire / 4) {
				dire++; j--;
			}
			else
				i++;
		}
		else if (dire % 4 == 2) {
			matrix[i][j] = num[k];
			if (j == dire / 4) {
				dire++; i--;
			}
			else
				j--;
		}
		else {
			matrix[i][j] = num[k];
			if (i == dire / 4 + 1) {
				dire++; j++;
			}
			else
				i--;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d", matrix[i][j]);
			if (j != n - 1)
				printf(" ");
		}
		printf("\n");
	}
	delete [] matrix;


#ifdef TEST
	system("pause");
#endif
	return 0;
}
