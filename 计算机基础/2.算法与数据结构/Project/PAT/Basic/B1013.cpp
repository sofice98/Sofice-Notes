#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>

#define TEST
using namespace std;
int isprime(int p) {
	for (int i = 2; i*i <= p; i++) {
		if (p%i == 0)	return 0;
	}
	return p;
}

int main()
{
	int n, m;
	scanf("%d %d", &m,&n);
	
	long int prime[10010] = {};
	long int temp = 2;
	int count = 1;
	for (int i = 1; i < 10010;) {
		if (isprime(temp)) {
			prime[i] = temp;
			++i;
		}
		temp++;
	}
	for (int i = m; i <= n; i++, count++) {
		if(count % 10 != 0 && i != n)
			printf("%ld ", prime[i]);
		else {
			printf("%ld\n", prime[i]);
		}
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}