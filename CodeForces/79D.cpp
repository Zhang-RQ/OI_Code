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

const int MAXN=1E4+10;

bool st[MAXN];
int n,k,l,f[1<<20],dis[25][25],id[MAXN],d[MAXN],tot;
vector<int> g[MAXN];
queue<int> q;

inline void add(int u,int v){g[u].push_back(v);g[v].push_back(u);}

void bfs(int s)
{
	memset(d,0x3f,sizeof d);d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int v:g[x])
			if(d[v]==0x3f3f3f3f)
				d[v]=d[x]+1,q.push(v);
	}
	for(int i=1;i<=n;i++)
		if(id[i])
			dis[id[i]][id[s]]=min(dis[id[i]][id[s]],d[i]);
}

int main()
{
	scanf("%d%d%d",&n,&k,&l);
	for(int i=1,x;i<=k;i++)
	{
		scanf("%d",&x);
		st[x-1]^=1;st[x]^=1;
	}
	for(int i=0;i<=n;i++)
		if(st[i]) id[i]=++tot;
	for(int i=1,x;i<=l;i++)
	{
		scanf("%d",&x);
		for(int j=1;j<=n-x+1;j++)
			add(j-1,j+x-1);//[j,j+x-1]
	}
	memset(dis,0x3f,sizeof dis);
	for(int i=0;i<=n;i++) if(id[i]) bfs(i);
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(int s=1;s<(1<<tot);s++)
		for(int i=0;i<tot;i++)
			if((s>>i)&1)
				for(int j=0;j<tot;j++)
					if((s>>j)&1)
						f[s]=min(f[s],f[s^(1<<i)^(1<<j)]+dis[i+1][j+1]);
	if(f[(1<<tot)-1]==0x3f3f3f3f) puts("-1");
	else printf("%d\n",f[(1<<tot)-1]);
}