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
const int INF=1<<30;

struct edge_t{
	int v,w,nxt;
}Edge[MAXN*4];

struct query_t{
	int x1,y1,x2,y2,id;
}Q[MAXN],tl[MAXN],tr[MAXN];

int Pool[MAXN*16],*id[MAXN],*cur=Pool,head[MAXN],cnt_e;
int dis[MAXN],Ans[MAXN],n,m,q,totp,X[MAXN],Y[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;

void add(int u,int v,int w)
{
	Edge[++cnt_e]=(edge_t){v,w,head[u]};
	head[u]=cnt_e;
}

void Dijkstra(int S,int x1,int x2,int y1,int y2)
{
	for(int i=x1;i<=x2;i++)
		for(int j=y1;j<=y2;j++)
			dis[id[i][j]]=INF;
	dis[S]=0;pq.push(make_pair(0,S));
	while(!pq.empty())
	{
		pair<int,int> x=pq.top();pq.pop();
		if(dis[x.second]!=x.first) continue;
		for(int _=head[x.second];_;_=Edge[_].nxt)
		{
			int v=Edge[_].v;
			if(!(x1<=X[v]&&X[v]<=x2&&y1<=Y[v]&&Y[v]<=y2)) continue;
			if(dis[v]>x.first+Edge[_].w)
				dis[v]=x.first+Edge[_].w,
				pq.push(make_pair(dis[v],v));
		}
	}
}

void solve(int x1,int x2,int y1,int y2,int ql,int qr)
{
	if(x1>x2||y1>y2||ql>qr) return;
	if(x2-x1>y2-y1)
	{
		int mid=(x1+x2)>>1,totl=0,totr=0;
		for(int y=y1;y<=y2;y++)
		{
			Dijkstra(id[mid][y],x1,x2,y1,y2);
			for(int i=ql;i<=qr;i++)
				Ans[Q[i].id]=min(Ans[Q[i].id],dis[id[Q[i].x1][Q[i].y1]]+dis[id[Q[i].x2][Q[i].y2]]);
		}
		for(int i=ql;i<=qr;i++)
		{
			int mnx=min(Q[i].x1,Q[i].x2),mxx=max(Q[i].x1,Q[i].x2);
			if(mxx<mid) tl[++totl]=Q[i];
			else if(mnx>mid) tr[++totr]=Q[i];
		}
		for(int i=1;i<=totl;i++)
			Q[ql+i-1]=tl[i];
		for(int i=1;i<=totr;i++)
			Q[qr-totr+i]=tr[i];
		solve(x1,mid-1,y1,y2,ql,ql+totl-1);
		solve(mid+1,x2,y1,y2,qr-totr+1,qr);
	}
	else
	{
		int mid=(y1+y2)>>1,totl=0,totr=0;
		for(int x=x1;x<=x2;x++)
		{
			Dijkstra(id[x][mid],x1,x2,y1,y2);
			for(int i=ql;i<=qr;i++)
				Ans[Q[i].id]=min(Ans[Q[i].id],dis[id[Q[i].x1][Q[i].y1]]+dis[id[Q[i].x2][Q[i].y2]]);
		}
		for(int i=ql;i<=qr;i++)
		{
			int mny=min(Q[i].y1,Q[i].y2),mxy=max(Q[i].y1,Q[i].y2);
			if(mxy<mid) tl[++totl]=Q[i];
			else if(mny>mid) tr[++totr]=Q[i];
		}
		for(int i=1;i<=totl;i++)
			Q[ql+i-1]=tl[i];
		for(int i=1;i<=totr;i++)
			Q[qr-totr+i]=tr[i];
		solve(x1,x2,y1,mid-1,ql,ql+totl-1);
		solve(x1,x2,mid+1,y2,qr-totr+1,qr);
	}
}

int main()
{
	memset(Ans,0x3f,sizeof Ans);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		id[i]=cur;cur+=m+1;
		for(int j=1;j<=m;j++)
			id[i][j]=++totp,X[id[i][j]]=i,Y[id[i][j]]=j;
	}
	for(int i=1,v;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&v);
			add(id[i][j],id[i][j+1],v);
			add(id[i][j+1],id[i][j],v);
		}
	for(int i=1,v;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&v);
			add(id[i][j],id[i+1][j],v);
			add(id[i+1][j],id[i][j],v);
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d%d%d",&Q[i].x1,&Q[i].y1,&Q[i].x2,&Q[i].y2),Q[i].id=i;
	solve(1,n,1,m,1,q);
	for(int i=1;i<=q;i++) printf("%d\n",Ans[i]);
}
