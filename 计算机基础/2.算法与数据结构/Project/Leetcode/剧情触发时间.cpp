#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;

//T(n)=o(n),S(n)=o(n)
vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
	int	c = 0, r = 0, h = 0;
	int size = requirements.size();
	vector<int> res(size, -1);
	vector<int> sum(size, 0);
	vector<pair<int, int>> cn;
	vector<pair<int, int>> rn;
	vector<pair<int, int>> hn;
	for (int j = 0; j < size; j++) {
		cn.push_back(make_pair(j, requirements[j][0]));
		rn.push_back(make_pair(j, requirements[j][1]));
		hn.push_back(make_pair(j, requirements[j][2]));
	}
	sort(cn.begin(), cn.end(), [](pair<int, int> a, pair<int, int> b) {return a.second < b.second; });
	sort(rn.begin(), rn.end(), [](pair<int, int> a, pair<int, int> b) {return a.second < b.second; });
	sort(hn.begin(), hn.end(), [](pair<int, int> a, pair<int, int> b) {return a.second < b.second; });

	for (int j = 0; j < requirements.size(); j++) {
		if (requirements[j][0] == 0 && requirements[j][1] == 0 && requirements[j][2] == 0) {
			res[j] = 0;
		}
	}
	int i = 0, j = 0, k = 0;
	for (int day = 0; day < increase.size(); day++) {
		c += increase[day][0];
		r += increase[day][1];
		h += increase[day][2];
		while (i < size && cn[i].second <= c) {
			if (++sum[cn[i].first] == 3) {
				if(res[cn[i].first] == -1)
					res[cn[i].first] = day + 1;
			}
			i++; 
		}
		while (j < size && rn[j].second <= r) {
			if (++sum[rn[j].first] == 3) {
				if (res[rn[j].first] == -1)
					res[rn[j].first] = day + 1;
			}
			j++;
		}while (k < size && hn[k].second <= h) {
			if (++sum[hn[k].first] == 3) {
				if (res[hn[k].first] == -1)
					res[hn[k].first] = day + 1;
			}
			k++;
		}
	}
	return res;




}

int main()
{
	vector<vector<int>> increase({{1,1,1}} );
	vector<vector<int>> requirements({{0,0,0}} );
	getTriggerTime(increase, requirements);

	



	return 0;
}