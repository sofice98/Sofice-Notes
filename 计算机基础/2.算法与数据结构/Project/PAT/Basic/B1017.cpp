#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<math.h>

#define TEST
using namespace std;

int main()
{
	int num[1010] = {};
	int quotient[1010] = {};
	char input[1010] = {};
	int j;
	int divisor, remainder = 0;
	scanf("%s %d", input ,&divisor);

	for (j = 0; input[j] != '\0'; j++) {
		num[j] = input[j] - '0';
	}
	//divisor = input[j + 1] - '0';
	for (int i = 0; i != j; i++) {
		if (remainder) {
			remainder *= 10;
			remainder += num[i];
			quotient[i] = remainder / divisor;
			remainder = remainder - divisor * quotient[i];
		}
		else if (num[i] / divisor) {
			quotient[i] = num[i] / divisor;
			remainder = num[i] - divisor * quotient[i];
		}
		else {
			quotient[i] = 0;
			remainder = num[i];
		}
	}
	for (int i = 0; i != j; i++) {
		if (i == 0 && quotient[0] == 0) { 
			if (quotient[1] == 0) {
				printf("0"); break;
			}
			continue; 
		}
		printf("%d", quotient[i]);
	}
	printf(" %d", remainder);


#ifdef TEST
	system("pause");
#endif
	return 0;
}