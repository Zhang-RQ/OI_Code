#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;
const int MAXM=8010;

struct edge_t{
	int v,nxt,l;
	double w;
}Edge[MAXM];

int head[MAXN],cnt_e,dis[MAXN][MAXN],a[MAXN],n,m,d[MAXN];
long double ways[MAXN][MAXN],f[MAXN],ans[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
queue<int> q;

bool OnG(int S,int u,int v,int w){return dis[S][u]+w==dis[S][v];}

void add(int u,int v,int l,double w)
{
	Edge[++cnt_e]=(edge_t){v,head[u],l,w};
	head[u]=cnt_e;
}

void Dijkstra(int S,int *D,long double *F)
{
	memset(D,0x3f,sizeof dis[0]);
	D[S]=0;F[S]=1;pq.push(make_pair(0,S));
	while(!pq.empty())
	{
		pair<int,int> x=pq.top();pq.pop();
		if(D[x.second]!=x.first) continue;
		for(int i=head[x.second];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(D[v]>x.first+Edge[i].l)
				D[v]=x.first+Edge[i].l,
				F[v]=F[x.second]*Edge[i].w,
				pq.push(make_pair(D[v],v));
			else
				if(D[v]==x.first+Edge[i].l)
					F[v]+=F[x.second]*Edge[i].w;
		}
	}
}

void solve(int S)
{
	for(int i=1;i<=n;i++)
		f[i]=0;
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=Edge[i].nxt)
			if(OnG(S,x,Edge[i].v,Edge[i].l))
				++d[x];
	for(int i=1;i<=n;i++)
		if(!d[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		if(x!=S)
			ans[x]+=a[S]*f[x]*ways[S][x];
		f[x]+=a[x]/ways[S][x];
		for(int i=head[x];i;i=Edge[i].nxt)
			if(OnG(S,Edge[i].v,x,Edge[i].l))
			{
				f[Edge[i].v]+=f[x]*Edge[i].w;
				if(!--d[Edge[i].v])
					q.push(Edge[i].v);
			}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int u,v,l;double w;
		scanf("%d%d%d%lf",&u,&v,&l,&w);
		add(u,v,l,w);add(v,u,l,w);
	}
	for(int i=1;i<=n;i++)
		Dijkstra(i,dis[i],ways[i]);
	for(int i=1;i<=n;i++)
			solve(i);
	for(int i=1;i<=n;i++)
		printf("%.10Lf\n",ans[i]);
}
