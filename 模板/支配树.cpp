#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int fa[MAXN],mpos[MAXN],ord[MAXN],siz[MAXN];
int n,m,dfn[MAXN],dft,fat[MAXN],sdom[MAXN],idom[MAXN],tag[MAXN];
vector<int> G[MAXN],Gr[MAXN],pnt[MAXN];

void update(int x,int y){if(dfn[y]<dfn[sdom[x]]) sdom[x]=y;}

int find(int x)
{
	if(x==fa[x]) return x;
	int rfa=fa[x];
	fa[x]=find(fa[x]);
	mpos[x]=dfn[sdom[mpos[x]]]>dfn[sdom[mpos[rfa]]]?mpos[rfa]:mpos[x];
	return fa[x];
}

void dfs(int x)
{
	dfn[x]=++dft;
	for(int v:G[x])
	{
		if(dfn[v]) continue;
		dfs(v);fat[v]=x;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		G[u].push_back(v),
		Gr[v].push_back(u);
	dfs(1);dfn[0]=1<<30;
	for(int i=1;i<=n;i++)
		fa[i]=i,mpos[i]=i,ord[i]=i;
	sort(ord+1,ord+1+n,[](int x,int y){return dfn[x]>dfn[y];});
	for(int i=1;i<=n;i++)
	{
		int x=ord[i];
		for(int v:Gr[x])
		{
			if(dfn[v]<dfn[x])
				update(x,v);
			else
				find(v),update(x,sdom[mpos[v]]);
		}
		pnt[sdom[x]].push_back(x);
		for(int p:pnt[fat[x]])
		{
			find(p);
			int z=mpos[p];
			if(sdom[z]==sdom[p])
				idom[p]=sdom[p];
			else
			{
				idom[p]=z;
				tag[p]=1;
			}
		}
		fa[x]=fat[x];
	}
	for(int i=n;i>=1;i--)
	{
		int x=ord[i];
		if(tag[x])
			idom[x]=idom[idom[x]];
	}
	for(int i=1;i<=n;i++)
	{
		int x=ord[i];
		siz[x]++;
		siz[idom[x]]+=siz[x];
	}
	for(int i=1;i<=n;i++)
		printf("%d%c",siz[i],"\n "[i!=n]);
}
