#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int n, t = 0, num;
	int flag[10001] = {};
	int input[101];
	int ans[101];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num);
		input[i] = num;
		while (num != 1) {
			if (num % 2 != 0)	num = 3 * num + 1;
			num /= 2;
			flag[num] = 1;
		}
	}
	for(int i = 0; i < n; i++) {
		if (flag[input[i]] == 0)
			ans[t++] = input[i];
	}
	sort(ans, ans + t, [](int a, int b) { return a < b; });
	while(t--) {
		printf("%d", ans[t]);
		if(t != 0)
			printf(" ");
	}
	system("pause");
	return 0;
}