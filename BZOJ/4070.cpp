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

const int MAXN=30010;
const int MAXM=30010*400;

struct __edge{
	int nxt,v,w;
}Edge[MAXM];

bool vis[MAXN];
int head[MAXN],cnt_e,n,m,lim,dis[MAXN],S,T;
vector<int> p[MAXN],tmp[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;

inline void add(int u,int v,int w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
	assert(cnt_e<MAXM);
}

void build()
{
	for(int i=lim;i<=n;i++)
		for(int v:p[i])
		{
			for(int j=v-i,cnt=1;j>=0;j-=i,++cnt)
				add(v,j,cnt);
			for(int j=v+i,cnt=1;j<n;j+=i,++cnt)
				add(v,j,cnt);
		}
	for(int i=1;i<lim;i++)
	{
		if(!p[i].size()) continue;
		memset(vis,0,sizeof vis);
		for(int v:p[i]) vis[v]=1;
		for(int j=0;j<i;j++)
		{
			int k=j,lst=vis[k]?k:-1;
			for(k=i+j;k<n;k+=i)
			{
				if(lst!=-1) add(lst,k,(k-lst)/i);
				if(vis[k]) lst=k;
			}
			k-=i;lst=vis[k]?k:-1;
			for(k=k-i;k>=0;k-=i)
			{
				if(lst!=-1) add(lst,k,(lst-k)/i);
				if(vis[k]) lst=k;
			}
		}
	}
}

void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[S]=0;pq.push(make_pair(0,S));
	while(!pq.empty())
	{
		pair<int,int> x=pq.top();pq.pop();
		if(dis[x.second]!=x.first) continue;
		for(int i=head[x.second];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(dis[v]<=dis[x.second]+Edge[i].w) continue;
			dis[v]=dis[x.second]+Edge[i].w;
			pq.push(make_pair(dis[v],v));
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);lim=sqrt(n);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y),p[y].push_back(x);
		if(i==1) S=x;
		if(i==2) T=x;
	}
	build();Dijkstra();
	if(dis[T]==dis[n]) printf("-1\n");
	else printf("%d\n",dis[T]);
}