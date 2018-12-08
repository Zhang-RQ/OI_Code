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

#define DEBUG fprintf(stderr,"Passsing Line %d in fuction \"%s\" . \n",__LINE__,__FUNCTION__);

const int MAXN=3E6+10;
const int MAXM=5E6+10;

struct _edge{int y,w,id;_edge(int _y=0,int _w=0,int _id=0){y=_y;w=_w;id=_id;}}; //y : pnt on trie

struct __edge{int v,w,nxt;};

int flag=0;

struct Graph{
	__edge Edge[MAXM];
	int head[MAXN],cnt_e;
	
	__edge& operator [] (int i){return Edge[i];}

	void add(int u,int v,int w)
	{
		Edge[++cnt_e].v=v;
		Edge[cnt_e].w=w;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}

	void clear(){memset(head,0,sizeof head);cnt_e=0;}
}G,T;

int n,m,k,cnt,PntID[MAXN],vid1[MAXN],vid2[MAXN];
vector<_edge> ein[MAXN],eout[MAXN];
ll dis[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;

struct Segment_out{
	int t[MAXN<<2];
	
	void build(int x,int l,int r)
	{
		t[x]=++cnt;
		if(l==r) return vid1[l]=t[x],void();
		int mid=(l+r)>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
		G.add(t[x],t[x<<1],0),G.add(t[x],t[x<<1|1],0);
	}

	void add(int x,int l,int r,int cl,int cr,int p,int w)
	{
		assert(cl<=cr&&1);
		if(cl<=l&&r<=cr) return G.add(p,t[x],w),void();
		int mid=(l+r)>>1;
		if(cl<=mid) add(x<<1,l,mid,cl,cr,p,w);
		if(cr>mid)  add(x<<1|1,mid+1,r,cl,cr,p,w);
	}
}T1;

struct Segment_in{
	int t[MAXN<<2];

	void build(int x,int l,int r)
	{
		t[x]=++cnt;
		if(l==r) return vid2[l]=t[x],void();
		int mid=(l+r)>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
		G.add(t[x<<1],t[x],0);G.add(t[x<<1|1],t[x],0);
	}

	void add(int x,int l,int r,int cl,int cr,int p,int w)
	{
		assert(cl<=cr);
		// assert(x<(MAXN<<2));
		// printf("x=%d [%d,%d] [%d:%d]\n",x,l,r,cl,cr);
		if(cl<=l&&r<=cr) return G.add(t[x],p,w),void();
		int mid=(l+r)>>1;
		if(cl<=mid) add(x<<1,l,mid,cl,cr,p,w);
		if(cr>mid)  add(x<<1|1,mid+1,r,cl,cr,p,w);
	}
}T2;

namespace Vtree{
	int stk[MAXN],vdfn[MAXN],ved[MAXN],vfa[MAXN],fa[MAXN]; //dfn on vt
	int dep[MAXN],dfn[MAXN],siz[MAXN],top[MAXN],son[MAXN],dft,pnt[MAXN];

	bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;}//return y in x

	void dfs_init(int x)
	{
		siz[x]=1;son[x]=0;
		for(int i=T.head[x];i;i=T[i].nxt)
		{
			int v=T[i].v;
			dep[v]=dep[x]+1;
			dfs_init(v);fa[v]=x;
			siz[x]+=siz[v];
			if(siz[son[x]]<siz[v]) son[x]=v;
		}
	}

	void dfs_init2(int x,int tp)
	{
		top[x]=tp;dfn[x]=++dft;
		if(son[x]) dfs_init2(son[x],tp);
		for(int i=T.head[x];i;i=T[i].nxt)
		{
			int v=T[i].v;
			if(v==son[x]) continue;
			dfs_init2(v,v);
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

	void solve(int x)
	{
		int tot=0,Top=0;
		for(auto e:ein[x]) pnt[++tot]=e.y;
		for(auto e:eout[x]) pnt[++tot]=e.y;
		sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		int _t=tot;
		for(int i=2;i<=_t;i++)
			pnt[++tot]=LCA(pnt[i-1],pnt[i]);
		sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		for(int i=1;i<=tot;i++)
		{
			vdfn[pnt[i]]=i;
			while(Top&&!inside(stk[Top],pnt[i])) ved[stk[Top--]]=i-1;
			vfa[pnt[i]]=stk[Top];
			stk[++Top]=pnt[i];
		}
		while(Top) ved[stk[Top--]]=tot;
		T1.build(1,1,tot);T2.build(1,1,tot);
		for(auto e:eout[x]) G.add(vid1[vdfn[e.y]],e.id,0);
		for(auto e:ein[x]) G.add(e.id,vid2[vdfn[e.y]],e.w);
		for(int i=2;i<=tot;i++)
		{
			int p=++cnt;
			int x1=pnt[i],y1=vfa[x1];
			T2.add(1,1,tot,vdfn[x1],ved[x1],p,dep[y1]);
			T1.add(1,1,tot,vdfn[y1],vdfn[x1]-1,p,0);
			if(ved[x1]<ved[y1]) 
				T1.add(1,1,tot,ved[x1]+1,ved[y1],p,0);
		}
		PntID[x]=++cnt;
		for(int i=1;i<=tot;i++)
		{
			int x1=pnt[i];
			T1.add(1,1,tot,vdfn[x1],ved[x1],vid2[vdfn[x1]],dep[x1]);
			G.add(vid2[vdfn[x1]],PntID[x],0);
		}
	}
}

void Dijkstra(int S)
{
	memset(dis,0x3f,sizeof dis);
	dis[S]=0;pq.push({0,S});
	while(!pq.empty())
	{
		auto x=pq.top();pq.pop();
		if(dis[x.second]!=x.first) continue;
		for(int i=G.head[x.second];i;i=G[i].nxt)
		{
			int v=G[i].v;
			if(dis[v]>dis[x.second]+G[i].w)
			{
				dis[v]=G[i].w+dis[x.second];
				pq.push({dis[v],v});
			}
		}
	}
}

void solve()
{
	G.clear();T.clear();
	scanf("%d%d%d",&n,&m,&k);cnt=0;
	for(int i=1;i<=n;i++) ein[i].clear(),eout[i].clear();
	for(int i=1,u,v,a,b;i<=m;i++)
	{
		scanf("%d%d%d%d",&u,&v,&a,&b);
		ein[v].push_back(_edge(b,a,i));
		eout[u].push_back(_edge(b,a,i));
	}
	for(int i=1,u,v;i<k;i++)
	{
		scanf("%d%d%*d",&u,&v);
		T.add(u,v,0);
	}
	flag=1;
	Vtree::dfs_init(1);
	Vtree::dfs_init2(1,1);
	++m;
	ein[1].push_back(_edge(1,0,m));
	cnt=m;
	for(int i=1;i<=n;i++) reverse(ein[i].begin(),ein[i].end());
	for(int i=1;i<=n;i++) reverse(eout[i].begin(),eout[i].end());
	for(int i=1;i<=n;i++) Vtree::solve(i);
	Dijkstra(m);
	for(int i=2;i<=n;i++) printf("%lld\n",dis[PntID[i]]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}