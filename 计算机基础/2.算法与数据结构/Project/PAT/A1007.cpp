#include <bits/stdc++.h>
#include<random>
#define TEST
#define INF 0x3f3f3f3f
using namespace std;
int arr[10010] = {};
int main()
{
	int k;
	scanf("%d", &k);
	bool allnegative = true;
	int left = 0, right = k - 1;
	int maxsum = -1, tmpsum = 0, tmpleft = 0;
	for (int i = 0; i < k; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] >= 0)
			allnegative = false;
		tmpsum += arr[i];
		if (tmpsum < 0) {
			tmpsum = 0;
			tmpleft = i + 1;
		}
		else if (maxsum < tmpsum) {
			maxsum = tmpsum;
			left = tmpleft;
			right = i;
		}
	}
	if (allnegative)
		printf("0 %d %d", arr[0], arr[k - 1]);
	else
		printf("%d %d %d", maxsum, arr[left], arr[right]);


#ifdef TEST
	system("pause");
#endif
	return 0;
}