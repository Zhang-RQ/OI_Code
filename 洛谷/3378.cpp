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
const int MAXM=1E5+10;

struct __edge{
	int v,nxt;
}Edge[MAXM];

int n,m,head[MAXN],cnt_e,val[MAXN],Val[MAXN],bl[MAXN],SCC,stk[MAXN],top,ins[MAXN],dfn[MAXN],low[MAXN],dft,f[MAXN],d[MAXN];
vector<int> g[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++dft;ins[stk[++top]=x]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		++SCC;
		while(stk[top]!=x)
		{
			bl[stk[top]]=SCC;
			Val[SCC]+=val[stk[top]];
			ins[stk[top--]]=0;
		}
		bl[x]=SCC;Val[SCC]+=val[x];ins[x]=0;
		--top;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int x=1;x<=n;x++)
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(bl[x]!=bl[v]) g[bl[x]].push_back(bl[v]),++d[bl[v]];
		}
	queue<int> q;
	for(int i=1;i<=SCC;i++)
		if(!d[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		f[x]+=Val[x];
		for(int v:g[x])
		{
			f[v]=max(f[v],f[x]);
			if(!--d[v]) q.push(v);
		}
	}
	int Ans=0;
	for(int i=1;i<=SCC;i++) Ans=max(Ans,f[i]);
	printf("%d\n",Ans);
}