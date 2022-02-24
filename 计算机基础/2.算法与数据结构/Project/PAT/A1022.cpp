#include <bits/stdc++.h>
#define TEST
using namespace std;
int n, m;
struct book {
	book() :id(), year() {}
	string id;
	string title;
	string auther;
	vector<string> keywords;
	string publisher;
	string year;
};
vector<book> books;
map<string, vector<string>> keyword;
void split(string s,vector<string> &v) {
	string::const_iterator it, jt;
	for (it = s.begin(),jt=s.begin(); it != s.end();) {
		if (*it == ' ') {
			string tmp(jt, it);
			v.push_back(tmp);
			jt = ++it;
		}
		else	++it;
	}
	string tmp(jt, it);
	v.push_back(tmp);
}
void split2(string s, vector<string> &v) {
	string::const_iterator it, jt; bool flag = true;
	for (it = s.begin(), jt = s.begin(); it != s.end();) {
		if (*it == ' ' && flag) {
			string tmp(jt, it);
			v.push_back(tmp);
			jt = ++it;
			flag = false;
		}
		else	++it;
	}
	string tmp(jt, it);
	v.push_back(tmp);
}

int main()
{	
	cin >> n;
	getchar();
	for (int i = 1; i <= n; i++) {
		book tmp;
		getline(cin, tmp.id);
		getline(cin, tmp.title);
		getline(cin, tmp.auther);
		string words, s;
		getline(cin, words);
		istringstream is(words);
		while (is >> s)keyword[s].push_back(tmp.id);
		getline(cin, tmp.publisher);
		getline(cin, tmp.year);
		books.push_back(tmp);
	}
	sort(books.begin(), books.end(), [](book b1, book b2) { return b1.id < b2.id; });
	cin >> m; 
	getchar();
	for (int i = 1; i <= m; i++) {
		vector<string> query;
		string s;
		getline(cin, s);
		split2(s, query);		
		cout << s << endl;
		bool flag = false;
		if (query[0] == "1:") {
			for(book e : books) {
				if (e.title == query[1]) {
					cout << e.id << endl; flag = true;
				}
			}
		}
		else if (query[0] == "2:") {
			for (book e : books) {
				if (e.auther == query[1]) {
					cout << e.id << endl; flag = true;
				}
			}
		}
		else if (query[0] == "3:") {
			sort(keyword[query[1]].begin(), keyword[query[1]].end());
			if (keyword[query[1]].size() > 0) {
				flag = true;
				for (string s : keyword[query[1]])
					cout << s << endl;
			}
		}
		else if (query[0] == "4:") {
			for (book e : books) {
				if (e.publisher == query[1]) {
					cout << e.id << endl; flag = true;
				}
			}
		}
		else if (query[0] == "5:") {
			for (book e : books) {
				if (e.year == query[1]) {
					cout << e.id << endl; flag = true;
				}
			}
		}
		if (!flag) cout << "Not Found" << endl;
	}
	



#ifdef TEST
	system("pause");
#endif
	return 0;
}