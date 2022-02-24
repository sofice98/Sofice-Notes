#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int n,m;
	scanf("%d %d", &n, &m);
	
	int array[100];
	for (int i = 0; i < n; i++) {
		scanf("%d", &array[i]);
	}
	for (int i = n - m % n; i < n; i++) {
		printf("%d ", array[i]);
	}
	for (int i = 0; i < n - m % n; i++) {
		printf("%d", array[i]);
		if (i != n - m % n - 1)
			printf(" ");
	}

	//system("pause");
	return 0;
}