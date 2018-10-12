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
const int MAXN=1E5+10;

int f[MAXS],n,a[MAXN];

void solve()
{
	memset(f,0,sizeof f);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[a[i]]++;
	for(int i=0;i<20;i++)
		for(int s=0;s<1<<20;s++)
			if((s>>i)&1)
				f[s]+=f[s^(1<<i)];
	ll Ans=0;
	for(int i=1;i<=n;i++)
		Ans+=f[a[i]];
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}