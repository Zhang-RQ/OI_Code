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
const int INF=1<<30;

struct _edge{int v,w,nxt;}Edge[MAXN<<1];

int stk[MAXN],Top,tot,pnt[MAXN],rl[MAXN],f[MAXN],h[MAXN],frm[MAXN],Ans[MAXN];
int head[MAXN],cnt_e,dft,n,q,dfn[MAXN],siz[MAXN],dep[MAXN],dis[MAXN],son[MAXN],top[MAXN],fa[MAXN];
vector<pair<int,int> > t[MAXN<<2];
vector<int> g[MAXN];

bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;}

void add(int u,int v,int w)
{
	Edge[++cnt_e].w=w;
	Edge[cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs1(int x,int fa)
{
	::fa[x]=fa;siz[x]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dep[v]=dep[x]+1;dis[v]=dis[x]+Edge[i].w;
		dfs1(v,x);siz[x]+=siz[v];
		if(siz[son[x]]<siz[v]) son[x]=v;
	}
}

void dfs2(int x,int tp)
{
	top[x]=tp;dfn[x]=++dft;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}

int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
}

void vbuild()
{
	sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
	tot=unique(pnt+1,pnt+1+tot)-pnt-1;
	int ntot=tot;
	for(int i=2;i<=ntot;i++)
		pnt[++tot]=LCA(pnt[i-1],pnt[i]);
	sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
	tot=unique(pnt+1,pnt+1+tot)-pnt-1;
	stk[Top=1]=pnt[1];
	for(int i=2;i<=tot;i++)
	{
		while(!inside(stk[Top],pnt[i])) --Top;
		g[stk[Top]].push_back(pnt[i]);
		stk[++Top]=pnt[i];
	}
}

void dfsv1(int x)
{
	f[x]=rl[x]?0:INF;
	for(int v:g[x])
		dfsv1(v),f[x]=min(f[x],f[v]+dis[v]-dis[x]);
}

void dfsv2(int x,int fa)
{
	h[x]=rl[x]?0:INF;
	if(fa) h[x]=min(h[x],min(f[fa],h[fa])+dis[x]-dis[fa]);
	for(int v:g[x])
		dfsv2(v,x);
}

void solve(int x,int l,int r)
{
	tot=0;
	for(int i=l;i<=r;i++) pnt[++tot]=i,rl[i]=1;
	for(auto v:t[x]) pnt[++tot]=v.second;
	vbuild();dfsv1(pnt[1]);dfsv2(pnt[1],0);
	for(int i=1;i<=tot;i++) g[pnt[i]].clear(),rl[pnt[i]]=0;
	for(auto v:t[x]) Ans[v.first]=min(Ans[v.first],min(f[v.second],h[v.second]));
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(x<<1,l,mid);solve(x<<1|1,mid+1,r);
}

void insert(int x,int l,int r,int cl,int cr,int id,int p)
{
	if(cl<=l&&r<=cr) return t[x].push_back(make_pair(id,p)),void();
	int mid=(l+r)>>1;
	if(cl<=mid) insert(x<<1,l,mid,cl,cr,id,p);
	if(cr>mid)  insert(x<<1|1,mid+1,r,cl,cr,id,p);
}

int main()
{
	memset(Ans,0x3f,sizeof Ans);
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	dfs1(1,0);dfs2(1,0);
	scanf("%d",&q);
	for(int i=1,l,r,x;i<=q;i++)
	{
		scanf("%d%d%d",&l,&r,&x);
		insert(1,1,n,l,r,i,x);
	}
	solve(1,1,n);
	for(int i=1;i<=q;i++) printf("%d\n",Ans[i]);
}