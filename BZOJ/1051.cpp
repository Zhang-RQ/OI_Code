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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E4+10;

bool ins[MAXN];
int n,m,bl[MAXN],stk[MAXN],top,SCC,dfn[MAXN],low[MAXN],dft,out[MAXN],siz[MAXN],Ans;
vector<int> g[MAXN],G[MAXN];
bitset<MAXN> rea[MAXN];
queue<int> q;

void tarjan(int x)
{
	ins[x]=1;stk[++top]=x;dfn[x]=low[x]=++dft;
	for(int j=0;j<g[x].size();j++)
	{
		int v=g[x][j];
		if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
		else if(ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		++SCC;
		while(stk[top]!=x)
		{
			bl[stk[top]]=SCC;ins[stk[top]]=0;
			--top;siz[SCC]++;
		}
		bl[x]=SCC;ins[x]=0;--top;siz[SCC]++;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),g[v].push_back(u);
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int x=1;x<=n;x++)
		for(int j=0;j<g[x].size();j++)
		{
			int v=g[x][j];
			if(bl[x]!=bl[v]) G[bl[v]].push_back(bl[x]),out[bl[x]]++;
		}
	for(int i=1;i<=SCC;i++)
	{
		rea[i][i]=1;
		if(!out[i]) q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=0;i<G[x].size();i++)
		{
			int v=G[x][i];
			if(!(--out[v])) q.push(v);
			rea[v]|=rea[x];
		}
	}
	for(int i=1;i<=SCC;i++)
		if(rea[i].count()==SCC)
			Ans+=siz[i];
	printf("%d\n",Ans);
}