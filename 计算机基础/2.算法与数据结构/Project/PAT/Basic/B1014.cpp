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
	char s1[70], s2[70], s3[70], s4[70];
	int flag = 1;
	char week[7][4] = {
		"MON","TUE","WED","THU","FRI","SAT","SUN"
	};
	scanf("%s %s %s %s", s1, s2, s3, s4);
	for (int i = 0; 1; i++) {
		if (s1[i] == s2[i]) {
			if (flag == 2) {
				if (s1[i] >= 'A' && s1[i] <= 'N'){
					printf("%02d:", s1[i] - 'A' + 10); break;
				}
				if (s1[i] >= '0' && s1[i] <= '9'){
					printf("%02d:", s1[i] - '0'); break;
				}
			}
			if (flag == 1 && s1[i]>='A' && s1[i]<='G') {
				printf("%s ", week[s1[i] - 'A']); flag = 2;
			}
		}
	}
	for (int i = 0; 1; i++) {
		if (s3[i] == s4[i] && ((s3[i] >= 'A' && s3[i] <= 'Z') || (s3[i] >= 'a' && s3[i] <= 'z'))) {
			printf("%02d", i); break;
		}
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}