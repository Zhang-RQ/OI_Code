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
const int MAXM=2E5+10;
const int MAXND=MAXN*33;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,m;
int son[MAXND][2],tg[MAXND],cnt,sg[MAXN],rt[MAXN];
bool siz[MAXND],vis[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void pushup(int x) {siz[x]=siz[son[x][0]]|siz[son[x][1]];}

void pushdown(int x,int bit)
{
	if(tg[x])
	{
		if((tg[x]>>bit)&1) swap(son[x][0],son[x][1]);
		tg[son[x][0]]^=tg[x];
		tg[son[x][1]]^=tg[x];
		tg[x]=0;
	}
}

void insert(int &x,int v,int bit)
{
	if(!x) x=++cnt;
	if(!~bit) return siz[x]=0,void();
	pushdown(x,bit);
	insert(son[x][(v>>bit)&1],v,bit-1);
	pushup(x);
}

int merge(int x,int y,int bit,int cur)
{
	if(!x||!y) return x|y;
	pushdown(x,bit);pushdown(y,bit);
	int z=++cnt;
	son[z][0]=merge(son[x][0],son[y][0],bit-1,cur);
	son[z][1]=merge(son[x][1],son[y][1],bit-1,cur|(1<<bit));
	if(~bit) pushup(z);
	return z;
}

int Query(int x,int cur,int bit)
{
	if(!~bit) return cur;
	pushdown(x,bit);
	if(siz[son[x][0]]) return Query(son[x][0],cur,bit-1);
	else return Query(son[x][1],cur|(1<<bit),bit-1);
}

void Dfs(int x,int cur,int bit)
{
	pushdown(x,bit);
	if(son[x][0]) Dfs(son[x][0],cur,bit-1);
	if(son[x][1]) Dfs(son[x][1],cur|(1<<bit),bit-1);
}

void dfs(int x,int fa)
{
	int xs=0;vis[x]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);xs^=sg[v];
	}
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		tg[rt[v]]^=xs^sg[v];
		rt[x]=merge(rt[x],rt[v],20,0);
	}
	insert(rt[x],xs,20);
	sg[x]=Query(rt[x],0,20);
}

void solve()
{
	memset(head,0,sizeof head);memset(son,0,sizeof son);memset(tg,0,sizeof tg);
	memset(vis,0,sizeof vis);memset(rt,0,sizeof rt);memset(siz,0,sizeof siz);
	cnt=cnt_e=0;siz[0]=1;
	scanf("%d%d",&n,&m);int Ans=0;
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i,0),Ans^=sg[i];
	puts(Ans?"Alice":"Bob");
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}