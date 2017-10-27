#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int getint()
{
	int r = 0, c = getchar();

	for (; c < 48; c = getchar());
	for (; c > 47; c = getchar())
		r = r * 10 + c - 48;

	return r;
}

const int mod = 10007;
const int mxn = 200005;
const int mxm = 400005;
const int P=10007;
int n;

int tt;
int hd[mxn];
int to[mxm];
int nt[mxm];

inline void addedge(int x, int y)
{
	nt[++tt] = hd[x], to[tt] = y, hd[x] = tt;
	nt[++tt] = hd[y], to[tt] = x, hd[y] = tt;
}

int val[mxn];

int ans1;
int ans2;

signed main()
{
	n = getint();

	for (int i = 1; i < n; ++i)
	{
		int x = getint();
		int y = getint();

		addedge(x, y);
	}

	for (int i = 1; i <= n; ++i)
		val[i] = getint();

	for (int u = 1; u <= n; ++u)
	{
		int tmp = 0;
		int sum = 0;

		for (int i = hd[u], v; i; i = nt[i])
		{
			v = to[i];

			ans1=max(tmp*val[v],ans1);
			(ans2+=sum*val[v])%=P;
			tmp=max(tmp,val[v]);
			(sum+=val[v])%=P;
		}
	}
	(ans2*=2)%=P;
	printf("%d %d\n", ans1, ans2);

	return 0;
}
