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
	int coefficient[1010] = {};
	int exponent[1010] = {};
	int c, i = 0;
	while (scanf("%d", &c) != EOF) {
		if (i % 2 == 0) {
			coefficient[i / 2] = c;
		}
		else {
			exponent[(i - 1) / 2] = c;
		}
		++i;
	}
	if (exponent[0] == 0) {
		printf("0 0");
	}
	else {
		for (int j = 0; j < i / 2; j++) {
			coefficient[j] *= exponent[j];
			--exponent[j];
		}
		for (int j = 0; j < i / 2; j++) {
			if(exponent[j] != -1)
				printf("%d %d", coefficient[j], exponent[j]);
			if (j != i / 2 - 1 && exponent[j+1] != -1) {
				printf(" ");
			}
		}
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}