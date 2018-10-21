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

const int MAXN=1E5+10;
const int MAXD=3.3E6+10;

int n,siz[MAXD],son[MAXD][2],rt,cnt,d[MAXN];
vector<pair<int,int> > g[MAXN];

void insert(int v)
{
	int x=rt;
	for(int i=30,now;~i;i--)
	{
		now=(v>>i)&1;
		if(!son[x][now]) son[x][now]=++cnt;
		x=son[x][now];siz[x]++;
	}
}

int query(int v)
{
	int x=rt,ret=0;
	for(int i=30,now;~i;i--)
	{
		now=(v>>i)&1;
		if(siz[son[x][!now]]) ret|=(!now)<<i,x=son[x][!now];
		else ret|=now<<i,x=son[x][now];
	}
	return ret^v;
}

void dfs(int x,int fa,int dep)
{
	insert(dep);d[x]=dep;
	for(auto v:g[x])
		if(v.first!=fa)
			dfs(v.first,x,dep^v.second);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),g[u].push_back({v,w}),g[v].push_back({u,w});
	dfs(1,0,0);
	int Ans=0;
	for(int i=1;i<=n;i++)
		Ans=max(Ans,query(d[i]));
	printf("%d\n",Ans);
}