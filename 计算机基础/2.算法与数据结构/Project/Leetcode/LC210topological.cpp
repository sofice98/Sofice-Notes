#include<bits/stdc++.h>
using namespace std;


//拓扑排序
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses, vector<int>());
    vector<int> degree(numCourses, 0);
    vector<int> res;
    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        degree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++)
        if (degree[i] == 0)  //找到所有度为0的点
            q.push(i);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);
        numCourses--;
        for (auto next : adj[curr])
            if (--degree[next] == 0)
                q.push(next);
    }
    
    if (numCourses != 0)    return {};
    else                    return res;
}



int main()
{
	vector<vector<int>> prerequisites({ { 0,1 } });
	canFinish(2, prerequisites);
	



	return 0;
}