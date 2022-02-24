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
int tonum(int* a) {
	int tmp;
	tmp = a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3];
	return tmp;
}
int* toarray(int a) {
	int* tmp = new int[4];
	tmp[3] = a % 10; a /= 10;
	tmp[2] = a % 10; a /= 10;
	tmp[1] = a % 10; a /= 10;
	tmp[0] = a % 10; 
	return tmp;
}

int main()
{
	int n;
	int* num=new int[4];
	scanf("%d", &n);
	int tmp1, tmp2, tmp3;
	num = toarray(n);
	if (num[0] == num[1] && num[1] == num[2] && num[2] == num[3])
		printf("%04d - %04d = 0000", n, n);
	else {
		while (1) {
			sort(num, num + 4, [](int c1, int c2) { return c1 > c2; });
			tmp1 = tonum(num);
			sort(num, num + 4, [](int c1, int c2) { return c1 < c2; });
			tmp2 = tonum(num);
			tmp3 = tmp1 - tmp2;
			printf("%04d - %04d = %04d\n", tmp1, tmp2, tmp3);
			if (tmp3 == 6174)
				break;
			num = toarray(tmp3);
		}
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}