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

const int MAXS=1<<20;

int n;
pair<int,int> f[MAXS];

inline pair<int,int> update(pair<int,int> a,int b)
{
	if(b>a.first) return make_pair(b,a.first);
	if(b>a.second) return make_pair(a.first,b);
	return a;
}

inline pair<int,int> update(pair<int,int> a,pair<int,int> b)
{
	if(a.first<b.first) swap(a,b);
	if(a.second<b.first) return make_pair(a.first,b.first);
	return a;
}

void solve()
{
	ll Ans=0;
	for(int s=(1<<20)-1;s;s--)
		f[s]=make_pair(0,0);
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		f[x]=update(f[x],x);
	}
	for(int i=0;i<20;i++)
		for(int s=(1<<20)-1;s;s--)
			if(!((s>>i)&1))
				f[s]=update(f[s],f[s^(1<<i)]);
	for(int s=1;s<1<<20;s++)
		Ans=max(Ans,1ll*s*f[s].first*f[s].second);
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}