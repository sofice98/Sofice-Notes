#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<math.h>
#include<stdlib.h>

#define TEST
using namespace std;

void trans(int a,int d) {
	if (a == 0)
		return;
	trans(a / d, d);
	printf("%d", a - a / d * d);
}

int main()
{
	int a, b, d;
	scanf("%d %d %d", &a, &b, &d);
	a += b;
	if (a == 0)
		printf("0");
	else
		trans(a, d);


#ifdef TEST
	system("pause");
#endif
	return 0;
}