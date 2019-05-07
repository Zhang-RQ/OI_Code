//Wrong Answer

#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5E4+10;

int sdom[MAXN],idom[MAXN],tag[MAXN];
int n,m,dfn[MAXN],ord[MAXN],dft,fa[MAXN],fat[MAXN],mpos[MAXN];
ll f[MAXN];
vector<int> G[MAXN],Gr[MAXN],pnt[MAXN],T[MAXN];

void update(int x,int y)
{
	if(dfn[y]<dfn[sdom[x]])
		sdom[x]=y;
}

int find(int x)
{
	if(x==fa[x])
		return x;
	int rfa=fa[x];
	fa[x]=find(fa[x]);
	mpos[x]=dfn[sdom[mpos[x]]]>dfn[sdom[mpos[rfa]]]?mpos[rfa]:mpos[x];
	return x;
}

void dfs(int x)
{
	dfn[x]=++dft;
	ord[dft]=x;
	for(int _=0;_<G[x].size();_++)
	{
		int v=G[x][_];
		if(dfn[v]!=1<<30)
			continue;
		dfs(v);fat[v]=x;
	}
}

void dfsT(int x)
{
	f[x]+=x;
	for(int _=0;_<T[x].size();_++)
	{
		int v=T[x][_];
		f[v]+=f[x],dfsT(v);
	}
}

void solve()
{
	for(int i=1;i<=n;i++)
		G[i].clear(),
		Gr[i].clear(),
		pnt[i].clear(),
		T[i].clear(),
		fa[i]=mpos[i]=i,
		dfn[i]=0,
		f[i]=sdom[i]=idom[i]=fat[i]=0;
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		G[u].push_back(v),
		Gr[v].push_back(u);
	dft=0;dfs(n);dfn[0]=1<<30;
	for(int i=dft;i;i--)
	{
        int x=ord[i];
        for(int v:Gr[x])
        {
			if(!dfn[v])
				continue;
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
                idom[p]=z,tag[p]=1;
        }
        fa[x]=fat[x];
	}
	for(int i=1;i<=dft;i++)
		if(tag[ord[i]])
			idom[ord[i]]=idom[idom[ord[i]]],tag[ord[i]]=0;
	for(int i=1;i<=dft;i++)
		T[idom[ord[i]]].push_back(ord[i]);
	dfsT(n);
	for(int i=1;i<=n;i++)
		printf("%I64d%c",dfn[i]?f[i]:0,"\n "[i!=n]);
}

int main()
{
	while(~scanf("%d%d",&n,&m))
		solve();
}
