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

const int MAXN=3E5+10;
const int MAXM=6E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,a[MAXN],n;
int jmp[MAXN][20],dep[MAXN];
ll f[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	jmp[x][0]=fa;dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=Edge[i].nxt)
		if(Edge[i].v!=fa)
			dfs(Edge[i].v,x);
}

void Dfs(int x,int fa)
{
	for(int i=head[x];i;i=Edge[i].nxt)
		if(Edge[i].v!=fa)
			Dfs(Edge[i].v,x),f[x]+=f[Edge[i].v];
}

void init()
{
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}

int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;~i;--i)
		if(dep[jmp[x][i]]>=dep[y])
			x=jmp[x][i];
	if(x==y) return x;
	for(int i=19;~i;--i)
		if(jmp[x][i]!=jmp[y][i])
			x=jmp[x][i],y=jmp[y][i];
	return jmp[x][0];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1,0);init();
	for(int i=2;i<=n;i++)
	{
		int LCA=lca(a[i-1],a[i]);
		f[a[i-1]]++;f[a[i]]++;
		f[LCA]--;f[jmp[LCA][0]]--;
	}
	Dfs(1,0);
	for(int i=2;i<=n;i++) f[a[i]]--;
	for(int i=1;i<=n;i++) printf("%lld\n",f[i]);
}