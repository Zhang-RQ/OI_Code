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
const int MAXK=51;

int d1[MAXN],dn[MAXN],f[MAXN][MAXK],d[MAXN],n,m,K,P,tps[MAXN],Tms,pnt[MAXN];
bool vis[MAXN];
vector<int> G0[MAXN];
vector<pair<int,int> > G[MAXN],Gr[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
queue<int> q;

void dijkstra(int s,int* dis,vector<pair<int,int> >* g)
{
	memset(dis,0x3f,sizeof d1);
	memset(vis,0,sizeof vis);
	dis[s]=0;pq.push(make_pair(0,s));
	while(!pq.empty())
	{
		pair<int,int> t=pq.top();pq.pop();
		if(vis[t.second]) continue;
		vis[t.second]=1;
		for(auto v:g[t.second])
		{
			if(dis[v.first]>t.first+v.second)
			{
				dis[v.first]=t.first+v.second;
				pq.push(make_pair(dis[v.first],v.first));
			}
		}
	}
}

void topo()
{
	for(int i=1;i<=n;i++) if(!d[i]) q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		tps[x]=++Tms;
		for(auto v:G0[x])
			if(!(--d[v])) q.push(v);
	}
}

void Solve()
{
	scanf("%d%d%d%d",&n,&m,&K,&P);Tms=0;
	for(int i=1;i<=n;i++) pnt[i]=i,G[i].clear(),Gr[i].clear(),G0[i].clear();
	memset(d,0,sizeof d);memset(tps,0,sizeof tps);memset(f,0,sizeof f);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back(make_pair(v,w));
		Gr[v].push_back(make_pair(u,w));
		if(w==0) G0[u].push_back(v),++d[v];
	}
	dijkstra(1,d1,G);dijkstra(n,dn,Gr);topo();
	sort(pnt+1,pnt+1+n,[](int a,int b)->bool{return d1[a]<d1[b]||(d1[a]==d1[b]&&tps[a]<tps[b]);});
	f[1][0]=1;	
	for(int k=0;k<=K;k++)
	{
		for(int i=1;i<=n;i++)
		{
			int x=pnt[i];
			for(auto v:G[x])
				if(d1[x]+v.second+k-d1[v.first]<=K)
					(f[v.first][d1[x]+v.second+k-d1[v.first]]+=f[x][k])%=P;
		}
	}
	bool fl=0;
	for(int i=1;i<=n;i++)
		if(d1[i]+dn[i]<=d1[n]+K&&d[i]) {fl=1;break;}
	if(fl) puts("-1");
	else
	{
		ll Ans=0;
		for(int i=0;i<=K;i++) (Ans+=f[n][i])%=P;
		printf("%lld\n",Ans);
	}
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;Solve());
}