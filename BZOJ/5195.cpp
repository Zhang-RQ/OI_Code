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

int n;
int siz[MAXN],dep[MAXN],val[MAXN];
char str[MAXN];
vector<int> g[MAXN];
ll Ans=1ll<<60,f[MAXN];

void dfs(int x)
{
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		dep[v]=dep[x]+val[v];
		dfs(v);siz[x]+=siz[v];
	}
	if(!g[x].size()) f[1]+=dep[x]-1;
}

void dfs2(int x,int fa)
{
	if(x!=1) f[x]=f[fa]+(siz[1]-siz[x])*3-siz[x]*val[x];
	if(g[x].size()) Ans=min(f[x],Ans);
	for(int i=0;i<g[x].size();i++)
		dfs2(g[x][i],x);
}

int main()
{
	scanf("%d",&n);
	for(int i=1,m;i<=n;i++)
	{
		scanf("%s%d",str+1,&m);
		val[i]=strlen(str+1)+1;
		if(!m) siz[i]=1;
		for(int j=1,x;j<=m;j++)
		{
			scanf("%d",&x);
			g[i].push_back(x);
		}
	}
	val[1]=dep[1]=0;
	dfs(1);dfs2(1,0);
	printf("%lld\n",Ans);
}