#include <bits/stdc++.h>
#define TEST
using namespace std;
map<string, pair<double, int>> school;

int main()
{	
	int n;
	cin >> n;
	set<string> s;
	while (n--) {
		string sch;
		int scoor;
		string id;
		cin >> id >> scoor >> sch;
		for (auto &c : sch)
			c = tolower(c);
		school[sch].second++;
		if (id[0] == 'B') 
			school[sch].first += scoor / 1.5;
		else if (id[0] == 'A') 
			school[sch].first += scoor;
		else 
			school[sch].first += scoor * 1.5;
		s.insert(sch);
	}
	vector<string> ans;
	for (auto e : s) {
		ans.push_back(e);
		school[e].first = (int)school[e].first;
	}
		
	sort(ans.begin(), ans.end(), [](string s1, string s2) {
		if (school[s1].first != school[s2].first)
			return school[s1].first > school[s2].first;
		else if (school[s1].second != school[s2].second)
			return school[s1].second < school[s2].second;
		else
			return s1 < s2;
	});
	printf("%d\n", ans.size());
	int count = 1; int lastscoor = school[ans[0]].first;
	for (int i = 0; i < ans.size(); i++) {
		if (school[ans[i]].first == lastscoor)
			printf("%d %s %.0f %d\n", count, ans[i].c_str(), school[ans[i]].first, school[ans[i]].second);
		else {
			count = i + 1;
			lastscoor = school[ans[i]].first;
			printf("%d %s %.0f %d\n", count, ans[i].c_str(), school[ans[i]].first, school[ans[i]].second);
		}
	}



#ifdef TEST
	system("pause");
#endif
	return 0;
}