#include <bits/stdc++.h>
#define TEST
using namespace std;
int gcd(long a, long b) {
	return a == 0 ? b : gcd(b%a, a);
}
void print(long a, long b) {
	if (a == 0) {
		printf("0"); return;
	}
	if (a / b != 0) {
		printf("%ld", a / b); 
		a -= (a / b)*b;
		if (a == 0)
			return;
		int tmp = gcd(a, b);
		a /= tmp;
		b /= tmp;
		printf(" %ld/%ld", a, b);
	}
	else {
		int tmp = gcd(a, b);
		a /= tmp;
		b /= tmp;
		printf("%ld/%ld", a, b);
	}
}
void fun(long a, long b) {
	if (a < 0 ^ b < 0)
		printf("(-");
	print(abs(a), abs(b));
	if (a < 0 ^ b < 0)
		printf(")");
}

int main()
{
	long a1,b1,a2,b2;
	scanf("%ld/%ld %ld/%ld", &a1, &b1, &a2, &b2);

	fun(a1, b1);
	printf(" + ");
	fun(a2, b2);
	printf(" = ");
	fun(a1*b2 + a2 * b1, b1*b2);
	printf("\n");

	fun(a1, b1);
	printf(" - ");
	fun(a2, b2);
	printf(" = ");
	fun(a1*b2 - a2 * b1, b1*b2);
	printf("\n");

	fun(a1, b1);
	printf(" * ");
	fun(a2, b2);
	printf(" = ");
	fun(a1*a2, b1*b2);
	printf("\n");

	fun(a1, b1);
	printf(" / ");
	fun(a2, b2);
	printf(" = ");
	if (a2 == 0)
		printf("Inf");
	else
		fun(a1*b2, a2 * b1);



#ifdef TEST
	system("pause");
#endif
	return 0;
}