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

const int MAXN=3E5+10;
const int MAXM=3E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM<<1];

char str[20];
int head[MAXN],cnt_e,dft,n,m,fafa;
int pos[MAXN],rev[MAXN],son[MAXN],siz[MAXN],top[MAXN],fa[MAXN],val[MAXN];
ll Ans[MAXN],sum[MAXN],num[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

struct __node{
	ll tag1,tag2,v;
	int sz,nsz;
}t[MAXN<<3];

void pushdown(int x,int l,int r)
{
	if(t[x].tag1)
	{
		int mid=(l+r)>>1;
		if(l==mid) t[x<<1].v+=num[rev[l]]*t[x].tag1;
		else t[x<<1].tag1+=t[x].tag1;
		if(mid+1==r) t[x<<1|1].v+=num[rev[r]]*t[x].tag1;
		else t[x<<1|1].tag1+=t[x].tag1;
		t[x].tag1=0;
	}
	if(t[x].tag2)
	{
		int mid=(l+r)>>1;
		if(l==mid) t[x<<1].v+=t[x].tag2*(t[x<<1].sz-t[x<<1].nsz);
		else t[x<<1].tag2+=t[x].tag2;
		if(mid+1==r) t[x<<1|1].v+=t[x].tag2*(t[x<<1|1].sz-t[x<<1|1].nsz);
		else t[x<<1|1].tag2+=t[x].tag2;
		t[x].tag2=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r) return t[x].v=Ans[rev[l]],t[x].sz=siz[rev[l]],t[x].nsz=siz[son[rev[l]]],void();
	int mid=(l+r)>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}

void change1(int x,int l,int r,int cl,int cr,ll dlt)
{
	if(l==r) return t[x].v+=num[rev[l]]*dlt,void();
	if(cl<=l&&r<=cr) return t[x].tag1+=dlt,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change1(x<<1,l,mid,cl,cr,dlt);
	if(cr>mid) change1(x<<1|1,mid+1,r,cl,cr,dlt);
}

void change2(int x,int l,int r,int cl,int cr,ll dlt)
{
	if(l==r) 
		return t[x].v+=dlt*(t[x].sz-t[x].nsz),void();
	if(cl<=l&&r<=cr) 
		return t[x].tag2+=dlt,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change2(x<<1,l,mid,cl,cr,dlt);
	if(cr>mid)  change2(x<<1|1,mid+1,r,cl,cr,dlt);
}

void change3(int x,int l,int r,int pos,ll dlt)
{
	if(l==r) return t[x].v+=dlt,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(pos<=mid) change3(x<<1,l,mid,pos,dlt);
	else change3(x<<1|1,mid+1,r,pos,dlt);
}

ll query(int x,int l,int r,int pos)
{
	if(l==r) return t[x].v;
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(pos<=mid) return query(x<<1,l,mid,pos);
	else return query(x<<1|1,mid+1,r,pos);
}

void dfs1(int x)
{
	siz[x]=1;sum[x]=val[x];
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		fa[v]=x;dfs1(v);
		siz[x]+=siz[v];
		sum[x]+=sum[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
	Ans[x]=1ll*val[x]*(siz[x]-1);
	num[x]=siz[x]-1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		Ans[x]+=sum[v]*(siz[x]-siz[v]);
		num[x]+=1ll*siz[x]*siz[v]-1ll*siz[v]*siz[v];
	}
}

void dfs2(int x,int tp)
{
	top[x]=tp;
	pos[x]=++dft;rev[pos[x]]=x;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==son[x]) continue;
		dfs2(v,v);
	}
}

void solve(int op,int x,ll dlt)
{
	if(op==1) change3(1,1,n,pos[x],dlt*(siz[x]-1));
	else change1(1,1,n,pos[x],pos[x]+siz[x]-1,dlt);
	if(x==1) return;
	int ls;ll W;
	if(op==1) W=dlt;
	else W=dlt*siz[x];
	if(x!=top[x])
	{
		x=fa[x];
		change2(1,1,n,pos[top[x]],pos[x],W);
		ls=top[x];x=fa[top[x]];
	}
	else ls=x,x=fa[x];
	while(x)
	{
		change3(1,1,n,pos[x],W*(siz[x]-siz[ls]));
		if(x==top[x])
		{
			ls=x;x=fa[x];
			continue;
		}
		x=fa[x];
		change2(1,1,n,pos[top[x]],pos[x],W);
		ls=top[x];x=fa[top[x]];
	}
}

int main()
{
	scanf("%d%d",&n,&m); 
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),add(fa,i);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	dfs1(1);dfs2(1,1);
	build(1,1,n);
	for(int i=1,u,dlt;i<=m;i++)
	{
		scanf("%s",str+1);
		if(str[1]=='S') scanf("%d%d",&u,&dlt),solve(1,u,dlt);
		else if(str[1]=='M') scanf("%d%d",&u,&dlt),solve(2,u,dlt);
		else
		{
			scanf("%d",&u);
			if(!num[u]) puts("0");
			else printf("%.6lf\n",2.0*query(1,1,n,pos[u])/num[u]);
		} 
	}
}