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

const int MAXN=2E5+10;

ll Ans[MAXN];
int n,m,tot;
vector<int> G[MAXN],T[MAXN];

namespace Graph{
	int dfn[MAXN],low[MAXN],dft,stk[MAXN],top;

	void tarjan(int x,int fa)
	{
		dfn[x]=low[x]=++dft;
		stk[++top]=x;
		for(int v:G[x])
			if(v!=fa)
			{
				if(dfn[v]) low[x]=min(low[x],low[v]);
				else
				{
					tarjan(v,x);
					low[x]=min(low[x],low[v]);
					if(low[v]>=dfn[x])
					{
						++tot;
						do{
							T[stk[top]].push_back(tot);
							T[tot].push_back(stk[top]);
							--top;
						}while(stk[top+1]!=v);
						T[x].push_back(tot);
						T[tot].push_back(x);
					}
				}
			}
	}
}

namespace Tree{
	int siz[MAXN];

	void dfs1(int x,int fa)
	{
		siz[x]=x<=n;
		for(int v:T[x])
			if(v!=fa)
				dfs1(v,x),siz[x]+=siz[v];
	}

	void dfs2(int x,int fa)
	{
		for(int v:T[x])
			if(v!=fa)
				dfs2(v,x);
		ll t=1;
		for(int v:T[x])
			if(v!=fa) Ans[x]+=t*siz[v],t+=siz[v];
			else Ans[x]+=t*(n-siz[x]),t+=n-siz[x];
	}
}

int main()
{
	scanf("%d%d",&n,&m);tot=n;
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	Graph::tarjan(1,0);Tree::dfs1(1,0);Tree::dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%lld\n",2*Ans[i]);
}