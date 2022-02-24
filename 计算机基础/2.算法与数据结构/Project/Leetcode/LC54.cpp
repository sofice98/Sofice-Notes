#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;


vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 0)  return vector<int>();
    int m = matrix[0].size();
    vector<int> res;
    int num = 0;
    int count = ceil((float)min(n,m) / 2);
    for (int i = 0; i < count; ++i) {
        for (int j = i; j < m - i; ++j) {
            res.push_back(matrix[i][j]);
            if (++num == m * n)     return res;
        }
        for (int j = i + 1; j < n - i; ++j) {
            res.push_back(matrix[j][m - i - 1]);
            if (++num == m * n)     return res;
        }
        for (int j = m - i - 2; j >= i; --j) {
            res.push_back(matrix[n - i - 1][j]);
            if (++num == m * n)     return res;
        }
        for (int j = n - i - 2; j >= i + 1; --j) {
            res.push_back(matrix[j][i]);
            if (++num == m * n)     return res;
        }
    }
    return res;
}
int main()
{
    vector<vector<int>> matrix({    {1, 2, 3, 4, 5},
                                    {6, 7, 8, 9, 10},
                                    {11, 12, 13, 14, 15},
                                    {16, 17, 18, 19, 20} });
	
    spiralOrder(matrix);


	return 0;
}