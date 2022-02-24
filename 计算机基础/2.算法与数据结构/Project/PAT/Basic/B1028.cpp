#include <bits/stdc++.h>
#define TEST
using namespace std;
struct People {
	char name[6];
	int year;
	int month;
	int day;
};
bool isreasonable(const People tmp) {
	if (tmp.year > 2014)
		return false;
	else if (tmp.year == 2014) {
		if(tmp.month > 9)
			return false;
		else if (tmp.month == 9) {
			if (tmp.day <= 6)	return true;
			else return false;
		}
		else return true;
	}
	else {
		if (tmp.year > 1814)
			return true;
		else if (tmp.year == 1814) {
			if (tmp.month > 9)
				return true;
			else if (tmp.month == 9) {
				if (tmp.day < 6)	return false;
				else return true;
			}
			else return false;
		}
		else return false;
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	static People people[100000];
	int count = 0;
	for (int i = 0; i < n; i++) {
		People tmp;
		scanf("%s %d/%d/%d", tmp.name, &tmp.year, &tmp.month, &tmp.day);
		if (isreasonable(tmp)) {
			people[count] = tmp;
			count++;
		}
	}
	printf("%d", count);
	if (count == 0)	return 0;
	sort(people, people + count, [](People p1,People p2) {
		if (p1.year == p2.year) {
			if (p1.month == p2.month) {
				if (p1.day == p2.day) {
					return true;
				}
				else return p1.day < p2.day;
			}
			else return p1.month < p2.month;
		}
		else return p1.year < p2.year;
	});
	printf(" %s %s", people[0].name, people[count - 1].name);


#ifdef TEST
	system("pause");
#endif
	return 0;
}