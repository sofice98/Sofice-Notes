#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;


vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() == 0)   return {};
    sort(intervals.begin(), intervals.end(), [](vector<int> a, vector<int> b) { return a[0] < b[0]; });
    vector<vector<int>> res{ intervals[0] };
    for (auto it = intervals.begin() + 1; it < intervals.end(); it++) {
        if ((*it)[0] <= res.back()[1]) {
            res.back()[1] = max((*it)[1], res.back()[1]);
            res.back()[0] = min((*it)[0], res.back()[0]);
        }
        else {
            res.push_back(*it);
        }
    }
       
    return res;

}

int main()
{
    vector<vector<int>> matrix({    {1, 3},
                                    {2, 6},
                                    {8, 10} });
	
    merge(matrix);


	return 0;
}