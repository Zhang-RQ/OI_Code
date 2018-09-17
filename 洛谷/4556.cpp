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

const int MAXN=100010;

struct node{
	int l,r,v,mx,ps;
}t[MAXN*70];

int n,m,cnt,rt[MAXN],dep[MAXN],top[MAXN],siz[MAXN],son[MAXN],fa[MAXN],Ans[MAXN];
vector<int> g[MAXN];

void pushup(int x){t[x].mx=max(t[t[x].l].mx,t[t[x].r].mx);t[x].ps=(t[x].mx==t[t[x].l].mx?t[t[x].l].ps:t[t[x].r].ps);}

void insert(int &x,int l,int r,int pos,int v)
{
	if(!x) x=++cnt;
	t[x].v+=v;
	if(l==r) return t[x].ps=l,t[x].mx=t[x].v,void();
	int mid=(l+r)>>1;
	if(pos<=mid) insert(t[x].l,l,mid,pos,v);
	else insert(t[x].r,mid+1,r,pos,v);
	pushup(x);
}

int merge(int x,int y,int l,int r)
{
	if(!x||!y) return x|y;
	int z=x,mid=(l+r)>>1;
	t[z].v=t[x].v+t[y].v;
	t[z].l=merge(t[x].l,t[y].l,l,mid);
	t[z].r=merge(t[x].r,t[y].r,mid+1,r);
	if(l==r) t[z].mx=t[z].v,t[z].ps=l;
	else pushup(z);
	return z;
}

void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	siz[x]=1;::fa[x]=fa;
	for(int v:g[x])
		if(v!=fa)
		{
			dfs1(v,x);
			siz[x]+=siz[v];
			if(siz[son[x]]<siz[v]) son[x]=v;
		}
}

void dfs2(int x,int tp)
{
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int v:g[x])
		if(v!=son[x]&&v!=fa[x])
			dfs2(v,v);
}

void dfs3(int x,int fa)
{
	for(int v:g[x])
		if(v!=fa)
			dfs3(v,x),rt[x]=merge(rt[x],rt[v],1,100000);
	Ans[x]=t[rt[x]].ps;
}

int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	return y;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
	dfs1(1,0);dfs2(1,1);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		int lca=LCA(x,y);
		insert(rt[x],1,100000,z,1);
		insert(rt[y],1,100000,z,1);
		insert(rt[lca],1,100000,z,-1);
		insert(rt[fa[lca]],1,100000,z,-1);
	}
	dfs3(1,0);
	for(int i=1;i<=n;i++)
		printf("%d\n",Ans[i]);
}