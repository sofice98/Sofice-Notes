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
struct mooncake {
	float amount;
	float totalprice;
	float unitprice;
};


int main()
{
	int n,d;
	scanf("%d %d", &n, &d);

	mooncake cakes[1010];
	float sum = 0.0;
	for (int i = 0; i < n; i++) {
		scanf("%f", &cakes[i].amount);
	}
	for (int i = 0; i < n; i++) {
		scanf("%f", &cakes[i].totalprice);
		cakes[i].unitprice = cakes[i].totalprice / cakes[i].amount;
	}
	sort(cakes, cakes + n, [](mooncake c1, mooncake c2) { return c1.unitprice > c2.unitprice; });
	for (int i = 0; i < n; i++) {
		if (cakes[i].amount < d) {
			sum += cakes[i].totalprice;
			d -= cakes[i].amount;
		}
		else {
			sum += cakes[i].unitprice * d;
			break;
		}
	}
	printf("%.2f", sum);


#ifdef TEST
	system("pause");
#endif
	return 0;
}