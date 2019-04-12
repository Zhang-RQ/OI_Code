#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MAXM=4E5+10;

struct edge_t{
	int v,w,nxt;
}Edge[MAXM];

struct dat{
	int u,v;
	ll w;

	bool operator < (const dat &rhs) const {return w<rhs.w;}
};

namespace Heap{
	struct node_t{
		int l,r,d;
		ll tag;
		dat v;
	}t[MAXM];

	int cnt;
	
	void apply_tag(int x,ll dlt)
	{
		t[x].v.w+=dlt;
		t[x].tag+=dlt;
	}

	void pushdown(int x)
	{
		if(t[x].tag)
		{
			if(t[x].l)
				apply_tag(t[x].l,t[x].tag);
			if(t[x].r)
				apply_tag(t[x].r,t[x].tag);
			t[x].tag=0;
		}
	}

	int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		pushdown(x);pushdown(y);
		if(t[y].v<t[x].v)
			swap(x,y);
		t[x].r=merge(t[x].r,y);
		if(t[t[x].l].d<t[t[x].r].d)
			swap(t[x].l,t[x].r);
		t[x].d=t[t[x].r].d+1;
		return x;
	}

	void push(int &x,dat val)
	{
		t[++cnt]=(node_t){0,0,0,0,val};
		x=merge(x,cnt);
	}

	void pop(int &x){pushdown(x);x=merge(t[x].l,t[x].r);}
}

using namespace Heap;

priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > pq;
ll dis[MAXN],Ans[MAXN];
int n,m,pre[MAXN],head[MAXN],cnt_e,rt[MAXN],dfn[MAXN],dfn_end[MAXN],dft;
vector<int> T[MAXN];

bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn_end[x];}

void add(int u,int v,int w)
{
	Edge[++cnt_e]=(edge_t){v,w,head[u]};
	head[u]=cnt_e;
}

void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[1]=0;pq.push({0,1});
	while(!pq.empty())
	{
		auto x=pq.top();pq.pop();
		if(dis[x.second]!=x.first)
			continue;
		for(int i=head[x.second];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(dis[v]>x.first+Edge[i].w)
			{
				pre[v]=x.second;
				dis[v]=x.first+Edge[i].w;
				pq.push({dis[v],v});
			}
		}
	}
}

void predfs(int x)
{
	dfn[x]=++dft;
	for(int v:T[x])
		predfs(v);
	dfn_end[x]=dft;
}

void dfs(int x)
{
	for(int v:T[x])
	{
		dfs(v);
		apply_tag(rt[v],dis[v]-dis[x]);
		rt[x]=merge(rt[x],rt[v]);
	}
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==pre[x]||pre[v]==x)
			continue;
		push(rt[x],(dat){x,v,dis[v]+Edge[i].w});
	}
	while(rt[x]&&inside(x,t[rt[x]].v.u)&&inside(x,t[rt[x]].v.v))
		pop(rt[x]);
	if(rt[x])
		Ans[x]=t[rt[x]].v.w;
	else
		Ans[x]=-1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),
		add(u,v,w),add(v,u,w);
	Dijkstra();
	for(int i=2;i<=n;i++)
		T[pre[i]].push_back(i);
	predfs(1);dfs(1);
	for(int i=2;i<=n;i++)
		printf("%lld\n",Ans[i]);
}
