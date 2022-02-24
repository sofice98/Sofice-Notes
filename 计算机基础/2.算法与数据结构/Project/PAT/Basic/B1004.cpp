#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
struct student {
	student() = default;
	student(int s) :score(s) {}
	char name[11] = {};
	char id[11] = {};
	int score = 0;
};

int main()
{
	int n; 
	student first,last(101),temp;
	scanf("%d", &n);
	while(n--) {
		scanf("%s %s %d", temp.name, temp.id, &temp.score);
		if (temp.score > first.score)	first = temp;
		if (temp.score < last.score) last = temp;
	}
	printf("%s %s\n", first.name, first.id);
	printf("%s %s\n", last.name, last.id);

	return 0;
}