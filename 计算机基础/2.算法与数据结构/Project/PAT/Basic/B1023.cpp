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
	int flag[10];
	for (int i = 0; i < 10; i++) {
		scanf("%d", &flag[i]);
	}
	for (int i = 1; i < 10; i++) {
		if (flag[i]) {
			printf("%d", i);
			flag[i]--;
			break;
		}
	}
	for (int i = 0; i < 10; ) {
		if (flag[i]) {
			printf("%d", i);
			flag[i]--;
		}
		else
			i++;
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}