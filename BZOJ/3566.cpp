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

const int MAXN=5E5+10;
const int MAXM=1E6+10;

struct __edge{
	int nxt,v;
	double w;
}Edge[MAXM];

int head[MAXN],cnt_e,n;
double f[MAXN],g[MAXN],Ans,p[MAXN];

inline void add(int u,int v,double w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
}

void dfs1(int x,int fa)
{
	f[x]=1-p[x];
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs1(v,x);
		f[x]*=(1-Edge[i].w+Edge[i].w*f[v]);
	}
}

void dfs2(int x,int fa)
{
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		double p=g[x]*f[x]/(1-Edge[i].w+Edge[i].w*f[v]);
		g[v]=p+(1-p)*(1-Edge[i].w);
		dfs2(v,x);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v,t;i<n;i++) scanf("%d%d%d",&u,&v,&t),add(u,v,t/100.0),add(v,u,t/100.0);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),p[i]=x/100.0;
	dfs1(1,0);g[1]=1;dfs2(1,0);
	for(int i=1;i<=n;i++) Ans+=1-f[i]*g[i];
	printf("%.6lf\n",Ans);
}