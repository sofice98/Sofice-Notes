#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

int isprime(int a) {
	if (a % 2 == 0 && a != 2) {
		return 0;
	}
	for (int i = 3; i * i <= a; i++) {
		if (a % i == 0) {
			return 0;
		}
	}
	return a != 1;
}


int main()
{
	int n;
	scanf("%d", &n);
	
	int flag = 1, sum = 0;
	vector<int> prime;
	if (n < 5) {
		printf("%d", sum);
		return 0;
	}
	for (int i = 3; i <= n; i++, flag = 1) {
		if (isprime(i))	prime.push_back(i);
	}
	for (auto i = prime.begin()+1; i != prime.end(); i++) {
		if (*i - *(i - 1) == 2)	++sum;
	}
	printf("%d", sum);

	//system("pause");
	return 0;
}