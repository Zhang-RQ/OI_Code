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
const int MAXM=5E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN],cnt_e,n,jmp[MAXN][18],d[MAXN],d2[MAXN],dep[MAXN],siz[MAXN];
vector<int> g[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

int LCA(int x,int y)
{
	if(dep[x]>dep[y]) swap(x,y);
	for(int j=17;~j;j--)
		if(dep[jmp[y][j]]>=dep[x])
			y=jmp[y][j];
	if(x==y) return x;
	for(int j=17;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int main()
{
	scanf("%d",&n);
	for(int i=1,v;i<=n;i++)
	{
		while(scanf("%d",&v)&&v)
		{
			add(v,i);++d[i];
			g[i].push_back(v);
		}
	}
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(!d[i]) q.push(i),dep[i]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(!--d[v])
			{
				int lca=g[v][0];
				for(int j=1;j<g[v].size();j++)
					lca=LCA(lca,g[v][j]);
				jmp[v][0]=lca;dep[v]=dep[lca]+1;++d2[lca];
				for(int j=1;j<=17;j++)
					jmp[v][j]=jmp[jmp[v][j-1]][j-1];
				q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		siz[i]=1;
		if(!d2[i]) q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front();q.pop();
		siz[jmp[x][0]]+=siz[x];
		if(!--d2[jmp[x][0]])
			q.push(jmp[x][0]);
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",siz[i]-1);
}