#include <bits/stdc++.h>
#define TEST
using namespace std;
int p, m, n;
struct student {
	int p = -1;
	int mid = -1;
	int fin = -1;
	int all = -1;
};
map<string, student> studentmap;

int main()
{	
	cin >> p >> m >> n;
	for (int i = 1; i <= p; i++) {
		string tmpid; int tmpp;
		cin >> tmpid >> tmpp;
		if (tmpp >= 200) {
			studentmap[tmpid].p = tmpp;
		}
	}
	for (int i = 1; i <= m; i++) {
		string tmpid; int tmpmid;
		cin >> tmpid >> tmpmid;
		if (studentmap.count(tmpid)) {
			studentmap[tmpid].mid = tmpmid;
		}
	}
	for (int i = 1; i <= n; i++) {
		string tmpid; int tmpfin;
		cin >> tmpid >> tmpfin;
		if (studentmap.count(tmpid)) {
			studentmap[tmpid].fin = tmpfin;
			
		}
	}
	vector<pair<string,student>> ans;
	for (auto e : studentmap) {
		if (e.second.mid > e.second.fin) {
			if (e.second.fin == -1)
				e.second.all = e.second.mid*0.4 + 0.5;
			else
				e.second.all = e.second.mid*0.4 + e.second.fin*0.6 + 0.5;
		}
		else
			e.second.all = e.second.fin;
		if (e.second.all >= 60)
			ans.push_back(make_pair(e.first, e.second));
	}
	sort(ans.begin(), ans.end(), [](pair<string, student> s1, pair<string, student> s2) {
		return (s1.second.all == s2.second.all) ? s1.first < s2.first : s1.second.all > s2.second.all;
	});
	for (auto e : ans) {
		cout << e.first << " " << e.second.p << " " << e.second.mid << " " << e.second.fin << " " << e.second.all << endl;
	}


#ifdef TEST
	system("pause");
#endif
	return 0;
}