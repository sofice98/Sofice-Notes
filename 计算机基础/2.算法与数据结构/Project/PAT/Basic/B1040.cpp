#include <bits/stdc++.h>
#define TEST
using namespace std;

int main()
{
	char str[100010] = {};
	scanf("%s", str);

	long long p = 0, pa = 0;
	long long count = 0;
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == 'P') 
			p++;
		else if (str[i] == 'A') 
			pa += p;
		else 
			count += pa;
	}
	printf("%d", (int)(count % 1000000007));


#ifdef TEST
	system("pause");
#endif
	return 0;
}