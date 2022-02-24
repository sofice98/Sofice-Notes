#include <bits/stdc++.h>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
int char2int(char c) {
	if (c >= '0'&&c <= '9')
		return c - '0';
	else if (c >= 'a'&&c <= 'z')
		return c - 'a' + 10;
	else
		return -1;
}

long long todecimal(char* n, int radix) {
	long long dec = 0;
	for (int i = 0; n[i] != '\0'; i++)
		dec = dec * radix + char2int(n[i]);
	return dec;
}
int compare(long long n1, char* n2, long long radix) {
	long long sum = 0;
	for (int i = 0; n2[i] != '\0'; i++){
		sum = sum * radix + char2int(n2[i]);
		if (sum > n1)
			return 1;
	}
	if (sum > n1)
		return 1;
	else if (sum < n1)
		return -1;
	else
		return 0;
}

void fun(long long n1,char* n2) {
	long long low = 0, high = 0;
	for (int i = 0; n2[i] != '\0'; i++) {
		if (low < char2int(n2[i]))
			low = char2int(n2[i]);
	}
	low++;
	if (low == 1)	++low;
	high = n1 > 1 ? n1 + 1 : low + 1;
	while (low < high){
		long long m = (low + high) / 2;
		if (compare(n1, n2, m) == 1)
			high = m;
		else if (compare(n1, n2, m) == -1)
			low = m;
		else {
			printf("%d", m);
			return;
		}
	}
	printf("Impossible");
	return;
}

int main()
{
	char n1[11] = {}, n2[11] = {};
	int tag, radix;
	scanf("%s %s %d %d", n1, n2, &tag, &radix);
	if (tag == 1)
		fun(todecimal(n1, radix), n2);
	else
		fun(todecimal(n2, radix), n1);


#ifdef TEST
	system("pause");
#endif
	return 0;
}