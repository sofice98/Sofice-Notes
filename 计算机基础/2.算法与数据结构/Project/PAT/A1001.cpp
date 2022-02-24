#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	int sum = a + b;
	if (sum == 0)
		printf("0");
	else {
		char ans[15];
		int i, flag;
		if (sum < 0)
			printf("-");
		sum = abs(sum);
		for (i = 0, flag = 0; sum != 0; i++) {
			if (flag && flag % 3 == 0)
				ans[i++] = ',';
			ans[i] = sum % 10 + '0';
			flag++;
			sum /= 10;
		}
		for (int j = i - 1; j >= 0; j--)
			printf("%c", ans[j]);
	}
	


#ifdef TEST
	system("pause");
#endif
	return 0;
}