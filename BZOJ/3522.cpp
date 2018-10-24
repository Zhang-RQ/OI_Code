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

const int MAXN=5010;
const int MAXM=5010;

struct __edge{
	short v,nxt;
}Edge[MAXM<<1];

int f[MAXN][MAXN],head[MAXN],cnt_e;
int mxdep[MAXN],n;
vector<int> g[MAXN];
ll Ans=0;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	f[x][0]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);mxdep[x]=max(mxdep[x],mxdep[v]+1);
	}
	g[x].resize(mxdep[x]+5);
	int lim=mxdep[x]+3;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		for(int j=1;j<=lim&&j<mxdep[v]+2;j++)
			Ans+=g[x][j]*f[v][j-1]+f[x][j]*g[v][j+1];
		for(int j=0;j<=lim&&j<mxdep[v]+2;j++)
		{
			g[x][j]+=g[v][j+1];
			if(j) g[x][j]+=f[x][j]*f[v][j-1],f[x][j]+=f[v][j-1];
		}
	}
	Ans+=g[x][0];
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1,0);
	printf("%lld\n",Ans);
}