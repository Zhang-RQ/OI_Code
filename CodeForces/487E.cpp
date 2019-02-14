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
#include<functional>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

struct node_t{
	int l,r,mn;
}t[MAXN<<2];

char str[233];
vector<int> G[MAXN],T[MAXN];
int rt[MAXN],a[MAXN],val[MAXN],cnt,tot,n,m,q;

void pushup(int x) {t[x].mn=min(t[t[x].l].mn,t[t[x].r].mn);}

void build(int &x,int l,int r)
{
	x=++cnt;
	if(l==r) return t[x].mn=a[l],void();
	int mid=(l+r)>>1;
	build(t[x].l,l,mid);
	build(t[x].r,mid+1,r);
	pushup(x);
}

void change(int x,int l,int r,int p,int v)
{
	if(l==r) return t[x].mn=v,void();
	int mid=(l+r)>>1;
	if(p<=mid) change(t[x].l,l,mid,p,v);
	else change(t[x].r,mid+1,r,p,v);
	pushup(x);
}

int query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x].mn;
	int mid=(l+r)>>1;
	if(qr<=mid) return query(t[x].l,l,mid,ql,qr);
	else if(ql>mid) return query(t[x].r,mid+1,r,ql,qr);
	else return min(query(t[x].l,l,mid,ql,qr),query(t[x].r,mid+1,r,ql,qr));
}

namespace Graph{
	int dfn[MAXN],low[MAXN],stk[MAXN],top,dft;

	void tarjan(int x,int fa)
	{
		dfn[x]=low[x]=++dft;
		stk[++top]=x;
		for(int v:G[x])
			if(v!=fa)
			{
				if(dfn[v]) low[x]=min(low[x],dfn[v]);
				else
				{
					tarjan(v,x);
					low[x]=min(low[x],low[v]);
					if(low[v]>=dfn[x])
					{
						++tot;
						do{
							T[tot].push_back(stk[top]);
							T[stk[top]].push_back(tot);
							--top;
						}while(stk[top+1]!=v);
						T[x].push_back(tot);
						T[tot].push_back(x);
					}
				}
			}
	}
}

namespace Tree{
	multiset<int> s[MAXN];
	int siz[MAXN],fa[MAXN],top[MAXN],son[MAXN],dep[MAXN],idx[MAXN],ord[MAXN],len[MAXN];

	void dfs1(int x,int fa)
	{
		if(x<=n) s[fa].insert(val[x]);
		Tree::fa[x]=fa;dep[x]=dep[fa]+1;
		siz[x]=1;
		for(int v:T[x])
			if(v!=fa)
			{
				dfs1(v,x);
				siz[x]+=siz[v];
				if(siz[son[x]]<siz[v]) son[x]=v;
			}
		if(x>n) val[x]=*s[x].begin();
	}

	void dfs2(int x,int tp)
	{
		top[x]=tp;
		if(son[x]) idx[son[x]]=idx[x]+1,dfs2(son[x],tp);
		for(int v:T[x])
			if(v!=son[x]&&v!=fa[x])
				idx[v]=1,dfs2(v,v);
	}

	void init()
	{
		dfs1(1,0);idx[1]=1;dfs2(1,1);
		for(int x=1;x<=tot;x++)
			if(top[x]==x)
			{
				int y=x;
				while(y) a[idx[y]]=val[y],y=son[y],++len[x];
				build(rt[x],1,len[x]);
			}
	}

	int Query(int x,int y)
	{
		int Ret=1<<30;
		while(top[x]!=top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			Ret=min(Ret,query(rt[top[x]],1,len[top[x]],idx[top[x]],idx[x]));
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		Ret=min(Ret,query(rt[top[x]],1,len[top[x]],idx[x],idx[y]));
		if(x>n) Ret=min(Ret,val[fa[x]]);
		return Ret;
	}

	void Change(int x,int v)
	{
		change(rt[top[x]],1,len[top[x]],idx[x],v);
		if(!fa[x]) return val[x]=v,void();
		int _p=*s[fa[x]].begin();
		s[fa[x]].erase(val[x]);
		s[fa[x]].insert(v);
		val[x]=v;
		if(_p!=*s[fa[x]].begin())
			val[fa[x]]=*s[fa[x]].begin(),
			change(rt[top[fa[x]]],1,len[top[fa[x]]],idx[fa[x]],val[fa[x]]);
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);tot=n;
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	Graph::tarjan(1,0);Tree::init();
	for(int i=1,x,y;i<=q;i++)
	{
		scanf("%s%d%d",str+1,&x,&y);
		if(str[1]=='A') printf("%d\n",Tree::Query(x,y));
		else Tree::Change(x,y);
	}
}