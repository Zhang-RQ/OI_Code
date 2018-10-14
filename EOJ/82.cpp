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

int n,q,dfn[MAXN],dft,dep[MAXN],jmp[MAXN][19],pnt[MAXN],siz[MAXN],stk[MAXN],top;
vector<int> g[MAXN];

namespace Vtree{
	namespace BIT{
		int t[MAXN];
		void add(int x,int v)
		{
			++x;
			for(;x<=n+1;x+=x&(-x))
				t[x]+=v;
		}
		int ask(int x)
		{
			++x;int ret=0;
			for(;x;x-=x&(-x))
				ret+=t[x];
			return ret;
		}
	}

	bool isr[MAXN],vis[MAXN];
	int siz[MAXN],Rt,rt,mx_rt,Lim;
	vector<pair<int,int> > G[MAXN];
	ll Ans;

	void add(int u,int v,int w){G[u].push_back({v,w});G[v].push_back({u,w});}

	void get_rt(int x,int fa,int sz)
	{
		int mx=0;siz[x]=1;
		for(auto v:G[x])
			if(v.first!=fa&&!vis[v.first])
				get_rt(v.first,x,sz),
				siz[x]+=siz[v.first],
				mx=max(mx,siz[v.first]);
		mx=max(mx,sz-siz[x]);
		if(mx<mx_rt) mx_rt=mx,rt=x;
	}

	void dfs_ins(int x,int fa,int dep,int f)
	{
		if(dep>Lim) return;
		if(isr[x]) BIT::add(dep,f);
		for(auto v:G[x])
			if(v.first!=fa&&!vis[v.first])
				dfs_ins(v.first,x,dep+v.second,f);
	}

	void dfs_que(int x,int fa,int dep)
	{
		if(dep>Lim) return;
		if(isr[x]) Ans+=BIT::ask(Lim-dep);
		for(auto v:G[x])
			if(v.first!=fa&&!vis[v.first])
				dfs_que(v.first,x,dep+v.second);
	}

	void solve(int x)
	{
		vis[x]=1;
		if(isr[x]) BIT::add(0,1);
		for(auto v:G[x])
		{
			if(vis[v.first]) continue;
			dfs_que(v.first,x,v.second);
			dfs_ins(v.first,x,v.second,1);
		}
		for(auto v:G[x])
			if(!vis[v.first])
				dfs_ins(v.first,x,v.second,-1);
		if(isr[x]) BIT::add(0,-1);
		for(auto v:G[x])
		{
			if(vis[v.first]) continue;
			mx_rt=1<<30;
			get_rt(v.first,x,siz[v.first]);
			solve(rt);
		}
	}

	void clear(int x,int fa)
	{
		vis[x]=0;isr[x]=0;siz[x]=0;
		for(auto v:G[x])
			if(v.first!=fa)
				clear(v.first,x);
		G[x].clear();
	}

	ll calc(int tot)
	{
		Ans=0;
		mx_rt=1<<30;
		get_rt(Rt,0,tot);
		solve(rt);
		clear(Rt,0);
		return Ans;
	}
}

inline bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;}// y in x

void dfs(int x,int fa)
{
	jmp[x][0]=fa;siz[x]=1;
	dep[x]=dep[fa]+1;dfn[x]=++dft;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x),siz[x]+=siz[v];
}

void init()
{
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=18;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=18;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int build_Vtree(int o)
{
	sort(pnt+1,pnt+1+o,[](int a,int b)->bool{return dfn[a]<dfn[b];});
	int _o=o;
	for(int i=1;i<_o;i++)
		pnt[++o]=LCA(pnt[i],pnt[i+1]),Vtree::isr[pnt[i]]=1,Vtree::isr[pnt[i+1]]=1;;
	sort(pnt+1,pnt+1+o,[](int a,int b)->bool{return dfn[a]<dfn[b];});
	o=unique(pnt+1,pnt+1+o)-pnt-1;
	Vtree::Rt=pnt[1];top=0;
	for(int i=1;i<=o;i++)
	{
		while(top&&!inside(stk[top],pnt[i])) --top;
		if(top) Vtree::add(stk[top],pnt[i],dep[pnt[i]]-dep[stk[top]]);
		stk[++top]=pnt[i];
	}
	return o;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	dfs(1,0);init();
	for(int i=1,m,k;i<=q;i++)
	{
		scanf("%d%d",&m,&k);
		for(int j=1;j<=m;j++)
			scanf("%d",&pnt[j]);
		Vtree::Lim=min(k,n);
		printf("%lld\n",Vtree::calc(build_Vtree(m)));
	}
}