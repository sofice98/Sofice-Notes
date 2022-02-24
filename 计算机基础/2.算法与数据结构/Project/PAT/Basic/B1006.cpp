#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n / 100; i++) {
		printf("B");
	}
	n -= n / 100 * 100;
	for (int i = 0; i < n / 10; i++) {
		printf("S");
	}
	n -= n / 10 * 10;
	for (int i = 1; i <= n; i++) {
		printf("%d",i);
	}
	//system("pause");
	return 0;
}