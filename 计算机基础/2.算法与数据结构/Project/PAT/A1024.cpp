#include <bits/stdc++.h>
#define TEST
using namespace std;
#define d(x) (x-'0')
char* n = new char[111];
int k;
char* getPDnum(char* n) {
	char m[111];
	strcpy(m, n);
	reverse(m, m + strlen(m));
	return m;
}
bool isPDnum(char* n) {
	return strcmp(n, getPDnum(n)) == 0;
}
void addPDnum(char* n) {
	char m[111], add[111];
	strcpy(m, getPDnum(n));
	int j = 0, tmpadd = 0;
	for (int i = strlen(n) - 1; i >= 0; i--, j++) {
		add[j] = (tmpadd + d(m[i]) + d(n[i])) % 10 + '0';
		tmpadd = (tmpadd + d(m[i]) + d(n[i])) / 10;
	}
	if (tmpadd) add[j++] = tmpadd + '0';
	add[j] = '\0';
	reverse(add, add + j);
	strcpy(n, add);
}

int main()
{	
	scanf("%s %d", n, &k);
	int i;
	for (i = 0; i <= k; i++) {
		if (isPDnum(n) || i == k) {
			printf("%s\n%d", n, i);
			break;
		}
		addPDnum(n);
	}



#ifdef TEST
	system("pause");
#endif
	return 0;
}