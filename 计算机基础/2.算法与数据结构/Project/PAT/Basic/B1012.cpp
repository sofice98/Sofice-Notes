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
	int n;
	scanf("%d", &n);
	
	int input[1001] = {};
	int sum = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &input[i]);
	}
	for (int i = 0; i < n; i++) {
		if (input[i] % 10 == 0) {
			sum += input[i];
		}
	}
	sum == 0 ? printf("N ") : printf("%d ", sum);
	sum = 0;
	for (int i = 0; i < n; i++) {
		if (input[i] % 5 == 1) {
			if(count % 2 == 0) {
				sum += input[i];
			} 
			else {
				sum -= input[i];
			}
			count++;
		}
	}
	count == 0 ? printf("N ") : printf("%d ", sum);
	sum = 0; count = 0;
	for (int i = 0; i < n; i++) {
		if (input[i] % 5 == 2) {
			++sum;
		}
	}
	sum == 0 ? printf("N ") : printf("%d ", sum);
	sum = 0;
	for (int i = 0; i < n; i++) {
		if (input[i] % 5 == 3) {
			sum += input[i];
			++count;
		}
	}
	sum == 0 ? printf("N ") : printf("%.1f ", (double)sum/ count);
	sum = 0;
	for (int i = 0; i < n; i++) {
		if (input[i] % 5 == 4 && sum < input[i]) {
			sum = input[i];
		}
	}
	sum == 0 ? printf("N") : printf("%d", sum);

#ifdef TEST
	system("pause");
#endif
	return 0;
}