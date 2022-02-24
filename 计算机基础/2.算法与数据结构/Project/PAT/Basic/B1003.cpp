#include<stdio.h>
#include<iostream> 
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
#include<cstring>
using namespace std;

int main() {
	int n = 0;
	char ch[100];
	scanf("%d", &n); 
	while (n--) {
		memset(ch, 0, 100);
		scanf("%s", ch);
		int i, p = 0, a = 0, c = 0, t = 0, b = 0;
		for (i = 0; ch[i] != '\0'; i++) {
			if (ch[i] == 'P' && !p)	p = 1;
			else if (ch[i] == 'T' && !t)	t = 1;
			else if (ch[i] == 'A') {
				if (p != 1)	a++;
				else if (p == 1 && t != 1) b++;
				else c++;
			}
			else {
				printf("NO\n");
				break;
			}
		}
		if (ch[i] != '\0') 	continue; 
		if (b != 0 && a * b == c && t == 1)	printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}