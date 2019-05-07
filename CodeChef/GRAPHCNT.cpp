#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;

int n,m,sdom[MAXN],idom[MAXN],dfn[MAXN],dft,tag[MAXN];
int fa[MAXN],siz[MAXN],fat[MAXN],mpos[MAXN],ord[MAXN];
vector<int> G[MAXN],Gr[MAXN],pnt[MAXN];

void update(int x,int y)
{
	if(dfn[sdom[x]]>dfn[y])
		sdom[x]=y;
}

int find(int x)
{
	if(x==fa[x])
		return x;
	int rfa=fa[x];
	fa[x]=find(fa[x]);
	mpos[x]=dfn[sdom[mpos[x]]]>dfn[sdom[mpos[rfa]]]?mpos[rfa]:mpos[x];
	return fa[x];
}

void dfs(int x)
{
	dfn[x]=++dft;
	ord[dft]=x;
	for(int v:G[x])
		if(!dfn[v])
			dfs(v),fat[v]=x;
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
		fa[i]=mpos[i]=i;
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
			idom[ord[i]]=idom[idom[ord[i]]];
	for(int i=dft;i;i--)
	{
		int x=ord[i];
		siz[x]++;
		siz[idom[x]]+=siz[x];
	}
	ll Ans=1ll*siz[1]*(siz[1]-1)/2;
	for(int i=2;i<=n;i++)
		if(idom[i]==1)
			Ans-=1ll*siz[i]*(siz[i]-1)/2;
	printf("%lld\n",Ans);
}
