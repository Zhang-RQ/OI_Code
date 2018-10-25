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

const int MAXN=1E6+10;

int n,h[MAXN],H[MAXN],bot[MAXN],son[MAXN],mx[MAXN],mxp[MAXN];
int *f[MAXN],Pool[MAXN*10],*ptr=Pool+1;
vector<int> g[MAXN];

void dfs1(int x,int fa)
{
	h[x]=1;bot[x]=x;
	for(int v:g[x])
		if(v!=fa)
		{
			dfs1(v,x);
			h[x]=max(h[x],h[v]+1);
			if(h[v]>h[son[x]]) son[x]=v,bot[x]=bot[v],H[bot[x]]=h[x]-h[bot[x]]+1;
		}
}

void dfs2(int x,int fa)
{
	if(son[x]) f[son[x]]=f[x]+1,dfs2(son[x],x),mx[x]=mx[son[x]],mxp[x]=mxp[son[x]]+1;
	else mx[x]=1;
	if(mx[x]==1) mxp[x]=0;
	f[x][0]++;
	for(int v:g[x])
		if(v!=fa&&v!=son[x])
		{
			f[v]=ptr;ptr+=2*(H[v]+1);
			dfs2(v,x);
			for(int i=0;i<=H[v];i++)
			{
				f[x][i+1]+=f[v][i];
				if(f[x][i+1]>mx[x]||(f[x][i+1]==mx[x]&&mxp[x]>i+1))
					mx[x]=f[x][i+1],mxp[x]=i+1;
			}
		}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		g[u].push_back(v);g[v].push_back(u);
	}
	dfs1(1,0);
	for(int i=1;i<=n;i++)
		H[i]=H[bot[i]];
	f[1]=ptr;ptr+=2*(H[1]+1);
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		printf("%d\n",mxp[i]);
}