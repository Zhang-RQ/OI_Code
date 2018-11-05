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
const int MAXM=2E5+10;
const ll INF=1ll<<60;

struct __edge{
	int nxt,v,w,id;
}Edge[MAXM<<1];

ll dis1[MAXN],disn[MAXN];
int head[MAXN],cnt_e,fa[MAXN],fa1[MAXN],fan[MAXN],pos[MAXN],n,m,s,t,stk[MAXN],top,U[MAXN],V[MAXN],W[MAXN],q,FaE[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;
map<int,int> mp;

inline void add(int u,int v,int w,int id)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].id=id;
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
}

void Dijkstra(int s,ll *D,int *Fa,bool f)
{
	memset(D,0x3f,sizeof dis1);
	D[s]=0;pq.push(make_pair(0,s));
	while(!pq.empty())
	{
		pair<ll,int> x=pq.top();pq.pop();
		if(x.first!=D[x.second]) continue;
		if(pos[x.second]) Fa[x.second]=pos[x.second];
		for(int i=head[x.second];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(D[v]>x.first+Edge[i].w)
			{
				if(f) Fa[v]=Fa[x.second];
				else Fa[v]=x.second,FaE[v]=Edge[i].id;
				D[v]=x.first+Edge[i].w;
				pq.push(make_pair(D[v],v));
			}
		}
	}
}

namespace Segment_Tree{
	ll t[MAXN<<3],Ans1,Ans2;
	
	void pushdown(int x)
	{
		if(t[x]!=INF)
		{
			t[x<<1]=min(t[x<<1],t[x]);
			t[x<<1|1]=min(t[x<<1|1],t[x]);
			t[x]=INF;
		}
	}

	void build(int x,int l,int r)
	{
		t[x]=INF;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	}

	void change(int x,int l,int r,int cl,int cr,ll v)
	{
		if(cl<=l&&r<=cr) return t[x]=min(t[x],v),void();
		int mid=(l+r)>>1;pushdown(x);
		if(cl<=mid) change(x<<1,l,mid,cl,cr,v);
		if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,v);
	}

	void dfs(int x,int l,int r)
	{
		if(l==r)
		{
			if(t[x]>Ans1) Ans1=t[x],Ans2=1;
			else if(t[x]==Ans1) ++Ans2;
			return;
		}
		int mid=(l+r)>>1;pushdown(x);
		dfs(x<<1,l,mid);dfs(x<<1|1,mid+1,r);
	}
}

int main()
{
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&U[i],&V[i],&W[i]);
		add(U[i],V[i],W[i],i);add(V[i],U[i],W[i],i);
	}
	s=1;t=n;
	Dijkstra(s,dis1,fa,0);
	for(int x=t;x;x=fa[x])
		stk[++top]=x;
	reverse(stk+1,stk+1+top);
	for(int i=2;i<=top;i++)
		mp[FaE[stk[i]]]=i-1;
	for(int i=1;i<=top;i++)
		pos[stk[i]]=i;
	Dijkstra(s,dis1,fa1,1);Dijkstra(t,disn,fan,1);
	Segment_Tree::build(1,1,top-1);
	for(int i=1;i<=m;i++)
	{
		if(mp.find(i)!=mp.end()) continue;
		int u=U[i],v=V[i],pu=fa1[u],pv=fan[v]-1;
		if(pu<=pv) Segment_Tree::change(1,1,top-1,pu,pv,dis1[u]+W[i]+disn[v]);
		swap(u,v);pu=fa1[u];pv=fan[v]-1;
		if(pu<=pv) Segment_Tree::change(1,1,top-1,pu,pv,dis1[u]+W[i]+disn[v]);
	}
	Segment_Tree::dfs(1,1,top-1);
	if(Segment_Tree::Ans1!=dis1[n]) printf("%lld %lld\n",Segment_Tree::Ans1,Segment_Tree::Ans2);
	else printf("%lld %d\n",Segment_Tree::Ans1,m);
}