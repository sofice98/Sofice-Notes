#include<bits/stdc++.h>
using namespace std;

//���ظ����֣������ظ�ʹ��
//����+��֦
void backtracking(vector<vector<int>>& ans, vector<int>& candidates, vector<int> current, int last_use, int rest_target) {
    if (rest_target == 0) {
        ans.push_back(current);
    }
    for (int i = last_use; i < candidates.size() && candidates[i] <= rest_target; i++) {
        if (i != last_use && candidates[i] == candidates[i - 1])
            continue;
        current.push_back(candidates[i]);
        backtracking(ans, candidates, current, i + 1, rest_target - candidates[i]);
        current.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> current;
    backtracking(ans, candidates, current, 0, target);
    return ans;
}

int main()
{
	vector<int> nums({ 2,5,2,1,2 });
    combinationSum2(nums, 5);
	
	return 0;
}