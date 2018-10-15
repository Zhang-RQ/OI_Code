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
const int MAXM=1E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

struct Query{
	Query(){}
	Query(int _x,int _f,int _id) {x=_x;f=_f;id=_id;}
	int x,f,id;
};

int head[MAXN],cnt_e,pos[MAXN],n,q,siz[MAXN],son[MAXN],top[MAXN],dft,fa[MAXN];
ll t[MAXN<<2],tg[MAXN<<2],Ans[MAXN];
vector<Query> Q[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void pushup(int x){t[x]=t[x<<1]+t[x<<1|1];}

void pushdown(int x,int l,int r)
{
	if(tg[x])
	{
		int mid=(l+r)>>1;
		t[x<<1]+=tg[x]*(mid-l+1);t[x<<1|1]+=tg[x]*(r-mid);
		tg[x<<1]+=tg[x];tg[x<<1|1]+=tg[x];
		tg[x]=0;
	}
}

void change(int x,int l,int r,int cl,int cr,int v)
{
	if(cl<=l&&r<=cr) return t[x]+=1ll*v*(r-l+1),tg[x]+=v,void();
	int mid=(l+r)>>1;pushdown(x,l,r);
	if(cl<=mid) change(x<<1,l,mid,cl,cr,v);
	if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,v);
	pushup(x);
}

ll query(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[x];
	int mid=(l+r)>>1;pushdown(x,l,r);
	ll ret=0;
	if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr);
	if(qr>mid)  ret+=query(x<<1|1,mid+1,r,ql,qr);
	return ret;
}

void dfs1(int x,int fa)
{
	siz[x]=1;::fa[x]=fa;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs1(v,x);siz[x]+=siz[v];
		if(siz[v]>siz[son[x]])
			son[x]=v;
	}
}

void dfs2(int x,int tp)
{
	pos[x]=++dft;top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}

void change(int x)
{
	while(x)
	{
		change(1,1,n,pos[top[x]],pos[x],1);
		x=fa[top[x]];
	}
}

ll query(int x)
{
	ll ret=0;
	while(x)
	{
		ret+=query(1,1,n,pos[top[x]],pos[x]);
		x=fa[top[x]];
	}
	return ret;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2,x;i<=n;i++)
		scanf("%d",&x),++x,add(i,x),add(x,i);
	dfs1(1,0);dfs2(1,1);
	for(int i=1,l,r,z;i<=q;i++)
	{
		scanf("%d%d%d",&l,&r,&z);++z;++l;++r;
		if(l) Q[l-1].push_back(Query(z,-1,i));
		Q[r].push_back(Query(z,1,i));
	}
	for(int i=1;i<=n;i++)
	{
		change(i);
		for(int j=0;j<Q[i].size();j++)
			Ans[Q[i][j].id]+=Q[i][j].f*query(Q[i][j].x);
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",Ans[i]%201314);
}