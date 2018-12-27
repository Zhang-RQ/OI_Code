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

const int MAXN=610;
const int MAXM=3E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int Ans,head[MAXN],cnt_e,G[MAXN][MAXN],n,m1,m2,stk[MAXN],top,dfn[MAXN],low[MAXN],dft,pnt[MAXN],tot;
bool ins[MAXN];

void add(int u,int v,int w)
{
	G[u][v]=min(G[u][v],w);
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void calc()
{
	int Res=0;
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			Res=max(Res,G[pnt[i]][pnt[j]]);
	Ans+=Res+1;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++dft;stk[++top]=x;ins[x]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		tot=0;
		while(stk[top]!=x)
		{
			ins[stk[top]]=0;
			pnt[++tot]=stk[top--];
		}
		ins[x]=0;top--;
		pnt[++tot]=x;
		calc();
	}
}

int main()
{
	scanf("%d%d%d",&n,&m1,&m2);
	memset(G,0x3f,sizeof G);
	for(int i=1;i<=n;i++) G[i][i]=0;
	for(int i=1,u,v;i<=m1;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v,1);add(v,u,-1);
	}
	for(int i=1,u,v;i<=m2;i++)
	{
		scanf("%d%d",&u,&v);
		add(v,u,0);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	for(int i=1;i<=n;i++)
		if(G[i][i]<0)
			return puts("NIE"),0;
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	printf("%d\n",Ans);
}