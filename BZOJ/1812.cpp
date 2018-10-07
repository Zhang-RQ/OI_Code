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

const int MAXN=210;
const int MAXM=210;
const int MAXK=120;

struct __edge{
	int nxt,v,w;
}Edge[MAXM];

int head[MAXN],cnt_e,dep[MAXN],siz[MAXN],w[MAXN];
int f[MAXN][MAXK][MAXN],n,k,tmp[MAXK][MAXN],stk[MAXN],top;

inline void add(int u,int v,int w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
}

void get_dep(int x)
{
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		dep[v]=dep[x]+Edge[i].w;
		get_dep(v);
	}
}

void dfs(int x)
{
	siz[x]=1;stk[++top]=x;
	for(int i=1;i<top;i++)
		f[x][0][stk[i]]=(dep[x]-dep[stk[i]])*w[x];
	f[x][1][x]=0;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		dfs(v);
		for(int j=0;j<=siz[x]+siz[v];j++)
			for(int l=0;l<=n;l++)
				tmp[j][l]=1<<30;
		for(int j=1;j<=top;j++)
			for(int l=0;l<=siz[v];l++)
				for(int o=0;o<=siz[x];o++)
					tmp[l+o][stk[j]]=min(tmp[l+o][stk[j]],f[v][l][stk[j]]+f[x][o][stk[j]]),
					tmp[l+o][stk[j]]=min(tmp[l+o][stk[j]],f[v][l][0]+f[x][o][stk[j]]);
		for(int j=0;j<=siz[x]+siz[v];j++)
			for(int l=1;l<=top;l++)
				f[x][j][stk[l]]=tmp[j][stk[l]];
		siz[x]+=siz[v];
	}
	for(int i=0;i<=siz[x];i++)
		f[x][i][0]=min(f[x][i][0],f[x][i][x]);
	top--;
}

int main()
{
	memset(f,0x3f,sizeof f);
	scanf("%d%d",&n,&k);++n;++k;
	for(int i=2,v,d;i<=n;i++)
	{
		scanf("%d%d%d",&w[i],&v,&d);++v;
		add(v,i,d);
	}
	get_dep(1);dfs(1);
	printf("%d\n",f[1][k][0]);
}