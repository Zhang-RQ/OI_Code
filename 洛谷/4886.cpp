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

bool vis[MAXN];
vector<pair<int,int> > g[MAXN];
int n,m,bl[MAXN],U[MAXN],V[MAXN],siz[MAXN],rt,mx_rt,dep[MAXN],Ans=1<<30;

void get_rt(int x,int fa,int sz)
{
	int mx=0;siz[x]=1;
	for(auto v:g[x])
		if(!vis[v.first]&&v.first!=fa)
			get_rt(v.first,x,sz),siz[x]+=siz[v.first],
			mx=max(mx,siz[v.first]);
	mx=max(mx,sz-siz[x]);
	if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs(int x,int fa,int p)
{
	bl[x]=p;
	for(auto v:g[x])
		if(v.first!=fa)
			dep[v.first]=dep[x]+v.second,dfs(v.first,x,p);
}

void solve(int x)
{
	vis[x]=1;dep[x]=0;
	for(auto v:g[x])
		dep[v.first]=v.second,dfs(v.first,x,v.first);
	int mx=0,lst=0;
	for(int i=1;i<=m;i++) mx=max(mx,dep[U[i]]+dep[V[i]]);
	Ans=min(Ans,mx);
	for(int i=1;i<=m;i++)
		if(dep[U[i]]+dep[V[i]]==mx)
		{
			if(bl[U[i]]!=bl[V[i]]) return;
			else
			{
				if(!lst) lst=bl[U[i]];
				else if(lst!=bl[U[i]]) return;
			}
		}
	mx_rt=1<<30;
	get_rt(lst,x,siz[lst]);
	if(vis[rt]) return;
	solve(rt);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	for(int i=1;i<=m;i++) scanf("%d%d",&U[i],&V[i]);
	mx_rt=1<<30;get_rt(1,0,n);solve(rt);
	printf("%d\n",Ans);
}