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
int tonum(char* a) {
	int tmp = 0;
	while (*a) {
		tmp *= 10; tmp += *a - '0';
		a++;
	}
	return tmp;
}

int main()
{
	char n[20000];
	scanf("%s", n);
	int indexE, accuracy, exponent;
	for (indexE = 0; 1; indexE++) {
		if (n[indexE] == 'E')	break;
	}
	accuracy = indexE - 3;
	exponent = tonum(n + indexE + 2);

	if(n[0]=='-')	printf("-");

	if (n[indexE + 1] == '+') {
		printf("%c", n[1]);
		for (int i = 3; i - 3 < exponent && n[i] != 'E'; i++) {
			printf("%c", n[i]);
		}
		if (tonum(n + indexE + 2) >= accuracy) {
			for (int i = accuracy; i < exponent; i++) {
				printf("0");
			}
		}
		else {
			printf(".");
			for (int i = accuracy + 4 - exponent; n[i] != 'E'; i++) {
				printf("%c", n[i]);
			}
		}
		
	}
	else {
		printf("0.");
		for (int i = 1; i < exponent; i++) {
			printf("0");
		}
		printf("%c", n[1]);
		for (int i = 3; n[i] != 'E'; i++) {
			printf("%c", n[i]);
		}
	}
	
	


#ifdef TEST
	system("pause");
#endif
	return 0;
}