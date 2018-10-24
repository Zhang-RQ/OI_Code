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
const int MAXM=2E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,h[MAXN],son[MAXN],bot[MAXN],H[MAXN];
ll *f[MAXN],*g[MAXN],Pool[MAXN*10],*ptr=Pool+1;
ll Ans;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs1(int x,int fa)
{
	h[x]=H[x]=1;bot[x]=x;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs1(v,x);h[x]=max(h[x],h[v]+1);
		if(h[son[x]]<h[v]) son[x]=v,bot[x]=bot[v],H[bot[x]]=h[x]-h[bot[x]]+1;
	}
}

void dfs2(int x,int fa)
{
	if(son[x])
		f[son[x]]=f[x]+1,g[son[x]]=g[x]-1,dfs2(son[x],x);
	f[x][0]++;Ans+=g[x][0];
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa||v==son[x]) continue;
		f[v]=ptr;ptr+=H[v]+1;
		g[v]=ptr+H[v]+1;ptr+=2*H[v]+2;
		dfs2(v,x);
		for(int j=H[v]-1;~j;j--)
		{
			if(j) Ans+=f[x][j-1]*g[v][j];
			Ans+=g[x][j+1]*f[v][j];
			g[x][j+1]+=f[x][j+1]*f[v][j];
		}
		for(int j=0;j<H[v];j++)
		{
			if(j) g[x][j-1]+=g[v][j];
			f[x][j+1]+=f[v][j];
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs1(1,0);
	for(int i=1;i<=n;i++)
		H[i]=H[bot[i]];
	f[1]=ptr;ptr+=H[1]+1;
	g[1]=ptr+H[1]+1;ptr+=2*H[1]+2;
	dfs2(1,0);
	printf("%lld\n",Ans);
}