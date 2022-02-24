#include <bits/stdc++.h>
#define TEST
using namespace std;


int main()
{
	int begin, end;
	scanf("%d %d", &begin, &end);

	float time = (end - begin) / 10;
	if ((int)time % 10 > 4)	time = (int)(time / 10) + 1;
	else time = (int)(time / 10);
	printf("%02d:%02d:%02d", ((int)time / 60) / 60, ((int)time / 60) % 60, (int)time % 60);

#ifdef TEST
	system("pause");
#endif
	return 0;
}