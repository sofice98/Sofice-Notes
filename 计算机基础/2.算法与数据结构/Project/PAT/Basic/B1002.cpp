#include<stdio.h>
#include<iostream> 
#include<algorithm>
#include<vector>
#include<string>
#include<stack>
using namespace std;

int main() {
	char n[100] = { };
	char c;
	string chn[10] = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu" };
	stack<string> result;
	int sum = 0, i = 0;
	while ((n[i] = getchar()) != '\n')
		i++; 
	n[i--] = '\0';
	for (; i>=0; i--) 
		sum += n[i]-'0';
	while (sum != 0) {
		int j = sum % 10;
		result.push(chn[j]);
		sum /= 10;
	}
	while (1) {
		printf("%s", result.top().c_str());
		result.pop();
		if (!result.empty()) {
			printf(" ");
			continue;
		}
		break;
	}
	return 0;
}
