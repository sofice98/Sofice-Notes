#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
struct student {
	int id;
	int c;
	int m;
	int e;
	int a;
	int c_p;
	int m_p;
	int e_p;
	int a_p;
};

int main() {

	int n, m;
	scanf("%d %d", &n, &m);
	student students[2000];
	int query[2000];
	for (int i = 0; i<n; i++) {
		scanf("%d %d %d %d", &students[i].id, &students[i].c, &students[i].m, &students[i].e);
		students[i].a = ((float)students[i].c + students[i].m + students[i].e) / 3.0;
	}
	for (int i = 0; i<m; i++) {
		scanf("%d", &query[i]);
	}
	stable_sort(students, students + n, [](const student &s1, const student &s2) {return s1.c > s2.c; });
	for (int i = 0,j = 0,pr = 0; i<n; i++) {
		if (students[i].c == pr) {
			students[i].c_p = j;
		}
		else {
			pr = students[i].c;
			students[i].c_p = i + 1;
			j = i + 1;
		}
	}
	stable_sort(students, students + n, [](const student &s1, const student &s2) {return s1.m > s2.m; });
	for (int i = 0, j = 0, pr = 0; i < n; i++) {
		if (students[i].m == pr) {
			students[i].m_p = j;
		}
		else {
			pr = students[i].m;
			students[i].m_p = i + 1;
			j = i + 1;
		}
	}
	stable_sort(students, students + n, [](const student &s1, const student &s2) {return s1.e > s2.e; });
	for (int i = 0, j = 0, pr = 0; i < n; i++) {
		if (students[i].e == pr) {
			students[i].e_p = j;
		}
		else {
			pr = students[i].e;
			students[i].e_p = i + 1;
			j = i + 1;
		}
	}
	stable_sort(students, students + n, [](const student &s1, const student &s2) {return s1.a > s2.a; });
	for (int i = 0, j = 0, pr = 0; i < n; i++) {
		if (students[i].a == pr) {
			students[i].a_p = j;
		}
		else {
			pr = students[i].a;
			students[i].a_p = i + 1;
			j = i + 1;
		}
	}
	for (int i = 0; i<m; i++) {
		student* thes = nullptr;
		for (int k = 0; k < n; k++) {
			if (students[k].id == query[i]) { 
				thes = &students[k]; break;
			}
		}
		if (thes == nullptr) {
			printf("N/A\n");
		}
		else {
			int j = thes->a_p;
			char t = 'A';
			if (thes->c_p < j) {
				j = thes->c_p; t = 'C';
			}
			if (thes->m_p < j) {
				j = thes->m_p; t = 'M';
			}
			if (thes->e_p < j) {
				j = thes->e_p; t = 'E';
			}
			printf("%d %c\n", j, t);
		}
	}
	return 0;
}