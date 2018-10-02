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

int n;
bool vis[MAXN];
ll f[MAXN],p[MAXN],dlt[MAXN],tmp[MAXN];
map<int,int> g[MAXN];
map<int,ll> mp[MAXN];
vector<int> gr[MAXN];

priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;

void Dijkstra()
{
	for(int i=1;i<=n;i++) f[i]=min(f[i],p[i]),pq.push(make_pair(f[i],i));
	while(!pq.empty())
	{
		int x=pq.top().second;ll c=pq.top().first;pq.pop();
		if(f[x]<c) continue;
		for(int i=0;i<gr[x].size();i++)
		{
			int v=gr[x][i];
			ll tc=c*g[v][x];
			if(tc<mp[x][v])
			{
				p[v]=p[v]-mp[x][v]+tc;
				mp[x][v]=tc;
				if(p[v]<f[v])
				{
					f[v]=p[v];
					pq.push(make_pair(f[v],v));
				}
			}
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,r;i<=n;i++)
	{
		scanf("%lld%lld%d",&p[i],&f[i],&r);
		if(r==0) f[i]=min(f[i],p[i]);
		for(int j=1,x;j<=r;j++)
		{
			scanf("%d",&x);
			g[i][x]++;gr[x].push_back(i);
		}
	}
	for(int i=1;i<=n;i++)
		for(map<int,int>::iterator it=g[i].begin();it!=g[i].end();++it)
			p[i]+=f[it->first]*it->second,mp[it->first][i]=f[it->first]*it->second;
	Dijkstra();
	printf("%lld\n",min(f[1],p[1]));
}