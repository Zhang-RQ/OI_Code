#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int n,a[MAXN],pre[MAXN],lst[MAXN];
map<int,int> mp;

bool solve(int L,int R)
{
	if(L>R) return 1;
	for(int i=L,j=R;i<=j;i++,j--)
	{
		if(pre[i]<L&&lst[i]>R)
			return solve(L,i-1)&&solve(i+1,R);
		if(pre[j]<L&&lst[j]>R)
			return solve(L,j-1)&&solve(j+1,R);
	}
	return 0;
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	mp.clear();
	for(int i=1;i<=n;i++)
	{
		pre[i]=mp[a[i]];
		mp[a[i]]=i;
	}
	mp.clear();
	for(int i=n;i>=1;i--)
	{
		int v=mp[a[i]];
		if(v) lst[i]=v;
		else lst[i]=n+1;
		mp[a[i]]=i;
	}
	puts(solve(1,n)?"non-boring":"boring");
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}