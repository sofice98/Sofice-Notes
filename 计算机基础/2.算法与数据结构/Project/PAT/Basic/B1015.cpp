#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<vector>
#include<stack>
#include<math.h>

#define TEST
using namespace std;
struct student {
	int id;
	int de;
	int cai;
};

bool cmp(student s1, student s2) {
	if (s1.de + s1.cai != s2.de + s2.cai)
		return s1.de + s1.cai > s2.de + s2.cai;
	else if (s1.de != s2.de)
		return s1.de > s2.de;
	else
		return s1.id < s2.id;
}

int main()
{
	int n,l,h;
	scanf("%d %d %d", &n, &l, &h);
	vector<student> type1,type2,type3,type4;
	student tmp;

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &tmp.id, &tmp.de, &tmp.cai);
		if (tmp.de >= l && tmp.cai >= l) {
			if (tmp.de >= h && tmp.cai >= h)
				type1.push_back(tmp);
			else if (tmp.de >= h)
				type2.push_back(tmp);
			else if (tmp.cai < h && tmp.de >= tmp.cai)
				type3.push_back(tmp);
			else 
				type4.push_back(tmp);
		}
	}
	sort(type1.begin(), type1.end(), cmp);
	sort(type2.begin(), type2.end(), cmp);
	sort(type3.begin(), type3.end(), cmp);
	sort(type4.begin(), type4.end(), cmp);

	printf("%d\n", type1.size() + type2.size() + type3.size() + type4.size());
	for (auto every : type1)
		printf("%d %d %d\n", every.id, every.de, every.cai);
	for (auto every : type2)
		printf("%d %d %d\n", every.id, every.de, every.cai);
	for (auto every : type3)
		printf("%d %d %d\n", every.id, every.de, every.cai);
	for (auto every : type4)
		printf("%d %d %d\n", every.id, every.de, every.cai);


#ifdef TEST
	system("pause");
#endif
	return 0;
}