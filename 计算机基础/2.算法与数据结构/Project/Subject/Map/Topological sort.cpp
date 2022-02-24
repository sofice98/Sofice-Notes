/*
Õÿ∆À≈≈–Ú
*/
#include<stdio.h>
#include<algorithm>
#include<random>
#include<time.h>
#include<iostream>
#include<string>
#include<queue>
#include<stack>
#include<set>
#include<fstream>
#define file
using namespace std;
int n, m;
string *active;
int *d;
int *f;
vector<int> *DAG;//1~n
bool *isvisited;
int *indegree;
stack<int> ans;

void dfs(int u) {
	for (auto v = DAG[u].begin(); v != DAG[u].end(); v++) {
		if (!isvisited[*v]) {
			dfs(*v);
			isvisited[*v] = true;
		}
	}
	ans.push(u);
}

void useIndegree() {
	stack<int> s;
	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0)
			s.push(i);
	}
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		printf("%s ", active[u].c_str());
		for (auto v = DAG[u].begin(); v != DAG[u].end(); v++) {
			if (--indegree[*v] == 0)
				s.push(*v);
		}
	}
}

int main() {
#ifdef file
	FILE *fp = fopen("Topological_sort.txt", "r");
	fscanf(fp, "%d %d", &n, &m);
#else
	scanf("%d %d", &n, &m);
#endif
	active = new string[n + 1];
	d = new int[n + 1]();
	f = new int[n + 1]();
	DAG = new vector<int>[n + 1];
	isvisited = new bool[n + 1]();
	indegree = new int[n + 1]();
	for (int i = 1; i <= n; i++) {
		char tmp[100];
#ifdef file
		fscanf(fp, "%s", tmp);
#else
		scanf("%s", tmp);
#endif
		active[i] = tmp;
	}
	for (int i = 1; i <= m; i++) {
		char tmp1[10], tmp2[10]; 
#ifdef file
		fscanf(fp, "%s %s", tmp1, tmp2);
#else
		scanf("%s %s", tmp1, tmp2);
#endif
		int u, v;
		for (int j = 1; j <= n; j++) {
			if (active[j] == (string)tmp1)
				u = j;
			if (active[j] == (string)tmp2)
				v = j;
		}
		indegree[v]++;
		DAG[u].push_back(v);
	}
	printf("DFS:\t\t");
	for (int i = 1; i <= n; i++) {
		if (!isvisited[i] && !indegree[i])
			dfs(i);
	}
	while (!ans.empty()) {
		printf("%s ", active[ans.top()].c_str());
		ans.pop();
	}
	printf("\nIndegree:\t");
	useIndegree();


	system("pause");
	return 0;
}