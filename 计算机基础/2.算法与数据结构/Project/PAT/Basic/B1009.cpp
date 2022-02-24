#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>

//#define TEST
using namespace std;

int main()
{
	//int n;
	//scanf("%d", &n);
	char c;
	char* sentence = new char[81];
	stack<string> output;
	string tmp("");
	
	while (scanf("%c", &c)) {
		if (c == ' ') {
			output.push(tmp);
			tmp = "";
		}
		else if (c == '\n') {
			output.push(tmp);
			break;
		}
		else {
			tmp += c;
		}
	}
	while (1) {
		cout << output.top();
		output.pop();
		if (output.empty()) {
			break;
		}
		cout << " ";
	}
#ifdef TEST
	system("pause");
#endif
	return 0;
}