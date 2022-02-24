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
	int n;
	scanf("%d", &n);

	char ta, tb;
	int awin = 0, bwin = 0;
	int ac = 0, aj = 0, ab = 0;
	int bc = 0, bj = 0, bb = 0;
	for (int i = 0; i < n; i++) {
		scanf(" %c %c", &ta, &tb);
		if (ta != tb) {
			if ((ta == 'C'&&tb == 'J') || (ta == 'J'&&tb == 'B') || (ta == 'B'&&tb == 'C')) {
				awin++; ta == 'C' || ta == 'J' ? (ta == 'C' ? ac++ : aj++) : ab++;
			}
			else {
				bwin++; tb == 'C' || tb == 'J' ? (tb == 'C' ? bc++ : bj++) : bb++;
			}
		}
	}
	printf("%d %d %d\n", awin, n - awin - bwin, bwin);
	printf("%d %d %d\n", bwin, n - awin - bwin, awin);
	if (ab >= ac) {
		if (ab >= aj) printf("B ");
		else printf("J ");
	}
	else {
		if (ac >= aj) printf("C ");
		else printf("J ");
	}

	if (bb >= bc) {
		if (bb >= bj) printf("B");
		else printf("J");
	}
	else {
		if (bc >= bj) printf("C");
		else printf("J");
	}

	


#ifdef TEST
	system("pause");
#endif
	return 0;
}