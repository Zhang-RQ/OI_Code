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

const int MAXN=100010<<3;
const int MAXM=200010<<5;

struct __edge{
	int v,nxt,w;
}Edge[MAXM];

ll dis[MAXN];
int head[MAXN],cnt_e,cnt,nd[2][MAXN],rt[2],n,m,s; //rt[0]:out rt[1]:in
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;

void add(int u,int v,int w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].w=w;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

struct node{
	int l,r;
}t[MAXN*2];

void build(int &x,int l,int r,int tp,int y)
{
	x=++cnt;
	if(l==r)
	{
		if(tp) add(x,y,0);
		return nd[tp][l]=x,void();
	}
	int mid=(l+r)>>1;
	build(t[x].l,l,mid,tp,t[y].l);build(t[x].r,mid+1,r,tp,t[y].r);
	if(!tp) add(t[x].l,x,0),add(t[x].r,x,0);
	else add(x,t[x].l,0),add(x,t[x].r,0),add(x,y,0);
}

void adde(int x,int l,int r,int cl,int cr,int tp,int dst,int w)
{
	if(cl<=l&&r<=cr)
	{
		if(tp) add(x,dst,w);
		else add(dst,x,w);
		return;
	}
	int mid=(l+r)>>1;
	if(cl<=mid) adde(t[x].l,l,mid,cl,cr,tp,dst,w);
	if(cr>mid)  adde(t[x].r,mid+1,r,cl,cr,tp,dst,w);
}

void Dijkstra(int S)
{
	memset(dis,0x3f,sizeof dis);dis[S]=0;
	pq.push({dis[S],S});
	while(!pq.empty())
	{
		pair<ll,ll> x=pq.top();pq.pop();
		if(dis[x.second]!=x.first) continue;
		for(int i=head[x.second];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(dis[v]>x.first+Edge[i].w)
			{
				dis[v]=x.first+Edge[i].w;
				pq.push({dis[v],v});
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&s);
	build(rt[0],1,n,0,0);
	build(rt[1],1,n,1,rt[0]);
	for(int i=1,t,l,r,x,w;i<=m;i++)
	{
		scanf("%d",&t);
		if(t==1) scanf("%d%d%d",&l,&r,&w),add(nd[0][l],nd[1][r],w);
		else if(t==2) scanf("%d%d%d%d",&x,&l,&r,&w),adde(rt[1],1,n,l,r,0,nd[0][x],w);
		else scanf("%d%d%d%d",&x,&l,&r,&w),adde(rt[0],1,n,l,r,1,nd[1][x],w);
	}
	Dijkstra(nd[1][s]);
	for(int i=1;i<=n;i++)
	{
		int p=nd[0][i];
		if(dis[p]==dis[0]) printf("-1 ");
		else printf("%lld ",dis[p]);
	}
	puts("");
}