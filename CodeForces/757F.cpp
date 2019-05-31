#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int n,m,s,jmp[MAXN][19],siz[MAXN],d[MAXN],dep[MAXN];
ll dis[MAXN];
vector<int> G2[MAXN],G2r[MAXN],T[MAXN];
vector<pair<int,int> > G[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;

void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;pq.emplace(0,s);
	while(!pq.empty())
	{
		auto x=pq.top();pq.pop();
		if(dis[x.second]!=x.first)
			continue;
		for(auto e:G[x.second])
		{
			if(dis[e.first]<=x.first+e.second)
				continue;
			dis[e.first]=x.first+e.second;
			pq.emplace(dis[e.first],e.first);
		}
	}
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	for(int j=18;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y)
		return x;
	for(int j=18;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),
		G[u].emplace_back(v,w),
		G[v].emplace_back(u,w);
	Dijkstra();
	for(int i=1;i<=n;i++)
		for(auto e:G[i])
			if(dis[i]+e.second==dis[e.first])
				G2[i].push_back(e.first),
				G2r[e.first].push_back(i),
				++d[e.first];
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		int fa=0;
		for(int v:G2r[x])
			if(!fa)
				fa=v;
			else
				fa=LCA(fa,v);
		if(fa)
			T[fa].push_back(x);
		jmp[x][0]=fa;dep[x]=dep[fa]+1;
		for(int j=1;j<=18;j++)
			jmp[x][j]=jmp[jmp[x][j-1]][j-1];
		for(int v:G2[x])
			if(!--d[v])
				q.push(v);
	}
	function<void(int)> dfs=[&](int x){siz[x]=1;for(int v:T[x]) dfs(v),siz[x]+=siz[v];};
	dfs(s);
	int Ans=0;
	for(int i=1;i<=n;i++)
		if(i!=s)
			Ans=max(Ans,siz[i]);
	printf("%d\n",Ans);
}
