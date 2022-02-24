#include <bits/stdc++.h>
#define TEST
using namespace std;



int main()
{	
	char num[25] = {};
	int doub[25] = {};
	int flag[10] = {};
	int tempadd = 0;
	scanf("%s", num);
	for (int i = strlen(num) - 1; i >= 0 ; i--) {
		flag[num[i] - '0']++;
		doub[i + 1] = ((num[i] - '0') * 2 + tempadd) % 10;
		flag[doub[i + 1]]--;
		tempadd = ((num[i] - '0') * 2 + tempadd) / 10;
	}
	
	if (tempadd) { 
		doub[0] = tempadd; 
		flag[tempadd]--;
	}
	for (int i = 0; i <= 9; i++) {
		if (flag[i] != 0) {
			printf("No\n"); break;
		}
		if(i==9)	printf("Yes\n");
	}
	for (int i = 0; i <= strlen(num); i++) {
		if (i == 0 && !tempadd)
			continue;
		printf("%d", doub[i]);
	}

		




#ifdef TEST
	system("pause");
#endif
	return 0;
}