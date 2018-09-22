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

const int MAXN=35;

int n,m,p,a,b,t[MAXN];
double f[1<<8][MAXN];
vector<pair<int,int> > g[MAXN];

void solve()
{
	for(int i=0;i<n;i++) scanf("%d",&t[i]);
	for(int i=1;i<=m;i++) g[i].clear();
	for(int i=1,u,v,w;i<=p;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back(make_pair(v,w));
		g[v].push_back(make_pair(u,w));
	}
	memset(f,0x42,sizeof f);
	f[(1<<n)-1][a]=0;
	for(int s=(1<<n)-1;~s;s--)
		for(int i=1;i<=m;i++)
			for(int j=0;j<n;j++)
				if((s>>j)&1)
					for(int k=0;k<g[i].size();k++)
						f[s^(1<<j)][g[i][k].first]=min(f[s^(1<<j)][g[i][k].first],f[s][i]+1.0*g[i][k].second/t[j]);
	double Ans=f[0][0];
	for(int s=0;s<1<<n;s++)
		Ans=min(Ans,f[s][b]);
	if(Ans>1E10) puts("Impossible");
	else printf("%lf\n",Ans);
}

int main()
{
	while(scanf("%d%d%d%d%d",&n,&m,&p,&a,&b)&&n) solve();
}