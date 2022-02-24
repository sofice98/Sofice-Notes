#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int table[25] = {};
	int num1[25] = {};
	int num2[25] = {};
	int carrybit = 0; 
	char c; int i;
	int len_table, len_num1, len_num2;
	for (i = 0; (c = getchar()) != '\n'; i++)
		table[i] = c - '0';
	len_table = i;
	for (i = 0; (c = getchar()) != '\n'; i++)
		num1[i] = c - '0';
	len_num1 = i;
	for (i = 0; (c = getchar()) != '\n'; i++)
		num2[i] = c - '0';
	len_num2 = i;
	reverse(table, table + len_table);
	reverse(num1, num1 + len_num1);
	reverse(num2, num2 + len_num2);
	
	for (int i = 0, tmp = 0; i < len_table; i++) {
		if (table[i] == 0) {
			tmp = (num1[i] + num2[i] + carrybit);
			carrybit = tmp / 10;
			num2[i] = tmp - carrybit * 10;
		}
		else {
			tmp = (num1[i] + num2[i] + carrybit);
			carrybit = tmp / table[i];
			num2[i] = tmp - carrybit * table[i];
		}
	}
	num2[len_table] = carrybit;
	reverse(num2, num2 + len_table + 1);
	for (int i = 0; i < len_table + 1; i++) {
		if (num2[i] != 0) {
			for (int j = i; j < len_table + 1; j++)
				printf("%d", num2[j]);
			break;
		}
		else if (i == len_table)
			printf("0");
	}



#ifdef TEST
	system("pause");
#endif
	return 0;
}
