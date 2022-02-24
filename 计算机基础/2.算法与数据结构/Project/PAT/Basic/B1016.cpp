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
	long long a, b, sum = 0;
	int da, db, count = 0;
	scanf("%lld %d %lld %d", &a, &da, &b, &db);

	while (a) {
		if (a % 10 == da) {
			sum += da * pow(10, count);count++; 
		}
		a /= 10;
	}
	count = 0;
	while (b) {
		if (b % 10 == db) {
			sum += db * pow(10, count); count++;
		}
		b /= 10;
	}
	printf("%d", sum);


#ifdef TEST
	system("pause");
#endif
	return 0;
}