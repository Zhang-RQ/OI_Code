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

const int MAXN=5E5+10;
const int MAXM=1E5+10;

struct __edge{
	int nxt,v,w;
}Edge[MAXM<<6];

struct node{
	int l,r;
}t[MAXN<<4];

int bel[MAXN],dlt[MAXN],d[MAXN];
int head[MAXN],cnt_e,cnt,nd[MAXN],rt,n,s,m,pv[MAXN],Val[MAXN]; // rt:in
queue<int> q;

inline void add(int u,int v,int w)
{
	d[u]++;
	Edge[++cnt_e].v=u;
	Edge[cnt_e].nxt=head[v];
	Edge[cnt_e].w=w;
	head[v]=cnt_e;
}

void build(int &x,int l,int r)
{
	x=++cnt;
	if(l==r)
	{
		add(x,l,0);nd[l]=x;
		return;
	}
	int mid=(l+r)>>1;
	build(t[x].l,l,mid);build(t[x].r,mid+1,r);
	add(x,t[x].l,0),add(x,t[x].r,0);
}

void adde(int x,int l,int r,int cl,int cr,int dst) //tp=0 dst -> [cl,cr]
{
	if(cl<=l&&r<=cr) return add(dst,x,0);
	int mid=(l+r)>>1;
	if(cl<=mid) adde(t[x].l,l,mid,cl,cr,dst);
	if(cr>mid)  adde(t[x].r,mid+1,r,cl,cr,dst);
}

void dfs(int x,int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	dfs(t[x].l,l,mid);dfs(t[x].r,mid+1,r);
}

int main()
{
	scanf("%d%d%d",&n,&s,&m);cnt=n+m;
	build(rt,1,n);
	for(int i=1,p,d;i<=s;i++)
	{
		scanf("%d%d",&p,&d);
		Val[nd[p]]=d;Val[p]=d;
	}
	for(int i=1,l,r,k,x,lst;i<=m;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		lst=l;
		for(int j=1;j<=k;j++)
		{
			scanf("%d",&x);
			add(x,i+n,1);
			if(x-1>=lst) adde(rt,1,n,lst,x-1,i+n);
			lst=x+1;
		}
		if(lst<=r) adde(rt,1,n,lst,r,i+n);
	}
	for(int i=1;i<=cnt;i++)
		if(!d[i])
			q.push(i),pv[i]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		pv[x]=max(Val[x],pv[x]);
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(Val[v]&&Val[v]<pv[x]+Edge[i].w) return puts("NIE"),0;
			pv[v]=max(pv[v],pv[x]+Edge[i].w);
			if(!(--d[v])) q.push(v);
		}
	}
	for(int i=1;i<=cnt;i++)
		if(d[i])
			return puts("NIE"),0;
	for(int i=1;i<=cnt;i++)
		if(pv[i]>1E9)
			return puts("NIE"),0;
	puts("TAK");
	for(int i=1;i<=n;i++)
		printf("%d%c",pv[i],i==n?'\n':' ');
}