#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>

#define TEST
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	long long a, b, c;
	for(int i = 1; i <= n; i++){
		scanf("%lld %lld %lld", &a, &b, &c);
		printf("Case #%d: %s\n", i, (a + b > c) ? "true" : "false");
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}