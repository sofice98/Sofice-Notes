#include <bits/stdc++.h>
#define TEST
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);

	static int input[100010];
	static int output[100010];
	static int max[100010];
	int count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &input[i]);
		output[i] = input[i];
		if (i == 0)	max[i] = input[i];
		else {
			if(input[i] > max[i-1])	max[i] = input[i];
			else max[i] = max[i - 1];
		}
	}
	sort(output, output + n);
	for (int i = 0; i < n; i++) {
		if (output[i] != input[i] || output[i] != max[i])
			output[i] = 0;
		else count++;
	}
	printf("%d\n", count);
	if (count == 0)
		printf("\n");
	else {
		for (int i = 0; i < n; i++) {
			if (output[i] != 0) {
				printf("%d", output[i]);
				if (count != 1) 	printf(" ");
				count--;
			}
		}
	}

#ifdef TEST
	system("pause");
#endif
	return 0;
}