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
}Edge[MAXM<<1];

int head[MAXN],cnt_e;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

int n,rt[MAXN],siz[MAXN],val[MAXN];
ll sum[MAXN],m,Ans;

struct __node{
	int l,r,d,v;
}t[MAXN];

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	if(t[x].v<t[y].v) swap(x,y);
	t[x].r=merge(t[x].r,y);
	if(t[t[x].l].d<t[t[x].r].d) swap(t[x].l,t[x].r);
	t[x].d=t[t[x].r].d+1;
	return x;
}

void dfs(int x)
{
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		dfs(v);
		rt[x]=merge(rt[x],rt[v]);
		sum[x]+=sum[v];siz[x]+=siz[v];
	}
	while(rt[x]&&sum[x]>m)
	{
		sum[x]-=t[rt[x]].v;siz[x]--;
		rt[x]=merge(t[rt[x]].l,t[rt[x]].r);
	}
	Ans=max(Ans,1ll*val[x]*siz[x]);
}

int main()
{
	scanf("%d%lld",&n,&m);
	for(int i=1,fa,c;i<=n;i++)
	{
		scanf("%d%d%d",&fa,&c,&val[i]);
		if(fa) add(fa,i);
		rt[i]=i;t[i].d=1;
		siz[i]=1;sum[i]=c;
		t[i].v=c;
	}
	dfs(1);printf("%lld\n",Ans);
}