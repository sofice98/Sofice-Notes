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


int main()
{
	char n[1010];
	scanf("%s", n);

	int flag[10] = {};

	for (int i = 0; n[i] != 0; i++) {
		flag[n[i] - '0']++;
	}
	for (int i = 0; i < 10; i++) {
		if (flag[i] != 0)
			printf("%d:%d\n", i, flag[i]);
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}