#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{	
	int d, n;
	vector<int> ans;
	scanf("%d %d", &d, &n);
	ans.push_back(d);
	while (--n) {
		vector<int> tmp;
		int start = 0, end = 0;
		for (end = 0; end < ans.size(); end++) {
			if (ans[start] != ans[end]) {
				tmp.push_back(ans[start]);
				tmp.push_back(end - start);
				start = end;
			}
		}
		tmp.push_back(ans[start]);
		tmp.push_back(end - start);
		ans = tmp;
	}
	for (auto e : ans)
		printf("%d", e);


#ifdef TEST
	system("pause");
#endif
	return 0;
}