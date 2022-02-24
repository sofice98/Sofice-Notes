/*
KMP
*/
#include<stdio.h>
#include<algorithm>
#include<random>
#include<time.h>
#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<fstream>
using namespace std;
int m, n;
char T[20] = " ababaca";
char S[30] = " bacbababaababacacabaca";
int *r;

void get_next() {
	int i = 1, j = 0;
	r[1] = 0;
	while (i <= m) {
		if (j == 0 || T[i] == T[j]) {
			++i; ++j; r[i] = j;
		}
		else
			j = r[j];
	}
}
int kmp() {
	int i = 1, j = 1;
	while (i <= n && j <= m) {
		if (j == 0 || S[i] == T[j]) {
			++i; ++j;
		}
		else
			j = r[j];
	}
	if (j > m)	return i - m;
	else return 0;
}



int main() {
	m = strlen(T) - 1;
	n = strlen(S) - 1;
	r = new int[m + 1]();
	get_next();
	printf("next:");
	for (int i = 1; i <= m; i++)
		printf(" %d", i);
	printf("\n     ");
	for (int i = 1; i <= m; i++)
		printf(" %d", r[i]);
	printf("\nKMP:index=%d\n", kmp());
	

	system("pause");
	return 0;
}