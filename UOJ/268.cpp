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

void Erase(multiset<ll> &s,ll x){s.erase(s.find(x));}

ll Mx2(multiset<ll> &s){return *s.rbegin()+*(++s.rbegin());}

char str[233];
int n,m,top[MAXN],siz[MAXN],son[MAXN],fa[MAXN],rt[MAXN],dep[MAXN],idx[MAXN],len[MAXN];
int U[MAXN],V[MAXN],W[MAXN];
multiset<ll> Ans,f[MAXN];
vector<int> T[MAXN];

namespace SegmentTree{
	struct node_t{
		int l,r;
		ll tag,lmx,rmx,mx,s,tAns,Ans;
	}t[MAXN*8];

	int cnt;

	void pushup(int x)
	{
		t[x].s=t[t[x].l].s+t[t[x].r].s;
		t[x].lmx=max(t[t[x].l].lmx,t[t[x].l].s+t[t[x].r].lmx);
		t[x].rmx=max(t[t[x].r].rmx,t[t[x].r].s+t[t[x].l].rmx);
		t[x].mx=max(t[t[x].l].rmx+t[t[x].r].lmx,max(t[t[x].l].mx,t[t[x].r].mx));
		t[x].tAns=max(t[t[x].l].tAns,t[t[x].r].tAns);
		t[x].Ans=max(t[x].tAns,t[x].mx);
	}

	void pushdown(int x)
	{
		if(t[x].tag)
		{
			t[t[x].l].mx+=t[x].tag;
			t[t[x].l].rmx+=t[x].tag;
			t[t[x].l].tag+=t[x].tag;
			t[t[x].l].tAns+=t[x].tag;
			t[t[x].r].mx+=t[x].tag;
			t[t[x].r].rmx+=t[x].tag;
			t[t[x].r].tag+=t[x].tag;
			t[t[x].r].tAns+=t[x].tag;
			t[x].tag=0;
		}
	}

	void build(int &x,int l,int r)
	{
		x=++cnt;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(t[x].l,l,mid);build(t[x].r,mid+1,r);
	}

	void changef(int x,int l,int r,int p,ll dlt)
	{
		if(l==r) return t[x].lmx+=dlt,t[x].rmx+=dlt,t[x].mx+=dlt,t[x].Ans=max(t[x].mx,t[x].tAns),void();
		int mid=(l+r)>>1;pushdown(x);
		if(p<=mid) changef(t[x].l,l,mid,p,dlt);
		else changef(t[x].r,mid+1,r,p,dlt);
		pushup(x);
	}

	void changev1(int x,int l,int r,int cl,int cr,ll dlt)
	{
		if(cl<=l&&r<=cr) return t[x].rmx+=dlt,t[x].mx+=dlt,t[x].tag+=dlt,t[x].tAns+=dlt,t[x].Ans=max(t[x].mx,t[x].tAns),void();
		int mid=(l+r)>>1;pushdown(x);
		if(cl<=mid) changev1(t[x].l,l,mid,cl,cr,dlt);
		if(cr>mid)  changev1(t[x].r,mid+1,r,cl,cr,dlt);
		pushup(x);
	}

	void changev2(int x,int l,int r,int p,ll dlt)
	{
		if(l==r) return t[x].mx+=dlt,t[x].lmx+=dlt,t[x].rmx+=dlt,t[x].s+=dlt,t[x].tAns+=dlt,t[x].Ans=max(t[x].mx,t[x].tAns),void();
		int mid=(l+r)>>1;pushdown(x);
		if(p<=mid) changev2(t[x].l,l,mid,p,dlt);
		else  changev2(t[x].r,mid+1,r,p,dlt);
		pushup(x);
	}

	void changemx2(int x,int l,int r,int p,ll dlt)
	{
		if(l==r) return t[x].tAns+=dlt,t[x].Ans=max(t[x].mx,t[x].tAns),void();
		int mid=(l+r)>>1;pushdown(x);
		if(p<=mid) changemx2(t[x].l,l,mid,p,dlt);
		else  changemx2(t[x].r,mid+1,r,p,dlt);
		pushup(x);
	}
}

using SegmentTree::t;

void dfs1(int x,int fa)
{
	::fa[x]=fa;
	dep[x]=dep[fa]+1;
	siz[x]=1;
	for(int v:T[x])
		if(v!=fa)
		{
			dfs1(v,x),siz[x]+=siz[v];
			if(siz[v]>siz[son[x]]) son[x]=v;
		}
}

void dfs2(int x,int tp)
{
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	idx[x]=dep[x]-dep[tp]+1;
	for(int v:T[x])
		if(v!=fa[x]&&v!=son[x])
			dfs2(v,v);
	if(!rt[tp]) SegmentTree::build(rt[tp],1,len[tp]=dep[x]-dep[tp]+1),f[fa[tp]].insert(0),Ans.insert(0);
}

void Changev1(int x,int y,ll dlt)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		Erase(Ans,t[rt[top[x]]].Ans);
		SegmentTree::changev1(rt[top[x]],1,len[top[x]],1,idx[x],dlt);
		Ans.insert(t[rt[top[x]]].Ans);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	Erase(Ans,t[rt[top[x]]].Ans);
	SegmentTree::changev1(rt[top[x]],1,len[top[x]],idx[x],idx[y],dlt);
	Ans.insert(t[rt[top[x]]].Ans);
}

void Changev2(int x,ll dlt)
{
	ll tMx=t[rt[top[x]]].lmx;
	Erase(Ans,t[rt[top[x]]].Ans);
	SegmentTree::changev2(rt[top[x]],1,len[top[x]],idx[x],dlt);
	Ans.insert(t[rt[top[x]]].Ans);
	ll nMx=t[rt[top[x]]].lmx;
	x=fa[top[x]];
	while(x)
	{
		ll tbeg=*f[x].rbegin(),tMx2=Mx2(f[x]);
		Erase(f[x],tMx);
		Erase(Ans,t[rt[top[x]]].Ans);
		ll ntMx=t[rt[top[x]]].lmx;
		f[x].insert(nMx);
		SegmentTree::changemx2(rt[top[x]],1,len[top[x]],idx[x],Mx2(f[x])-tMx2);
		SegmentTree::changef(rt[top[x]],1,len[top[x]],idx[x],*f[x].rbegin()-tbeg);
		Ans.insert(t[rt[top[x]]].Ans);
		tMx=ntMx;nMx=t[rt[top[x]]].lmx;
		x=fa[top[x]];
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

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++) f[i].insert(0),f[i].insert(0);
	for(int i=1,t;i<=m;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='+')
		{
			scanf("%d%d%d",&U[i],&V[i],&W[i]);
			int lca=LCA(U[i],V[i]);
			Changev1(U[i],V[i],W[i]);
			Changev1(lca,lca,-W[i]);
			Changev2(lca,W[i]);
		}
		else
		{
			scanf("%d",&t);
			int lca=LCA(U[t],V[t]);
			Changev1(U[t],V[t],-W[t]);
			Changev1(lca,lca,W[t]);
			Changev2(lca,-W[t]);
		}
		printf("%lld\n",*Ans.rbegin());
	}
}
