#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=5010;

char str[MAXN];
int n,m,q,c[MAXN],visp[MAXN],col[MAXN],vis[MAXN][MAXN],Ans[MAXN][MAXN],fa[MAXN];
vector<int> G[MAXN],nG[MAXN];
vector<pair<int,int> > Es,En;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int dfs1(int x)
{
	int ret=1;
	visp[x]=1;
	for(int v:G[x])
		if(!visp[v]&&c[x]==c[v]&&c[v]==0)
			col[v]=col[x]^1,ret&=dfs1(v);
		else if(c[x]==c[v]&&c[v]==0)
			ret&=col[x]!=col[v];
	return ret;
}

int dfs2(int x)
{
	int ret=1;
	visp[x]=1;
	for(int v:G[x])
		if(!visp[v]&&c[x]==c[v]&&c[v]==1)
			col[v]=col[x]^1,ret&=dfs2(v);
		else if(c[x]==c[v]&&c[v]==1)
			ret&=col[x]!=col[v];
	return ret;
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)
		c[i]=str[i]=='1';
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
		if(c[u]==c[v])
			Es.emplace_back(u,v);
		else
			En.emplace_back(u,v);
	}
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(auto e:En)
	{
		int x=find(e.first),y=find(e.second);
		if(x!=y)
		{
			nG[e.first].push_back(e.second);
			nG[e.second].push_back(e.first);
			fa[x]=y;
		}
	}
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(auto e:Es)
	{
		int x=find(e.first),y=find(e.second);
		if(x!=y)
		{
			nG[e.first].push_back(e.second);
			nG[e.second].push_back(e.first);
			fa[x]=y;
		}
	}
	for(int i=1;i<=n;i++)
		if(find(i)==i)
		{
			if(c[i]==0)
			{
				int f=dfs1(i);
				if(!f)
					nG[i].push_back(i);
			}
			else
			{
				int f=dfs2(i);
				if(!f)
					nG[i].push_back(i);
			}
		}
	queue<pair<int,int> > Q;
	for(int i=1;i<=n;i++)
	{
		Q.emplace(i,i);
		vis[i][i]=Ans[i][i]=1;
		for(int v:nG[i])
			if(c[i]==c[v]&&!vis[i][v])
			{
				vis[i][v]=vis[v][i]=1;
				Ans[i][v]=Ans[v][i]=1;
				Q.emplace(i,v);
			}
	}
	while(!Q.empty())
	{
		pair<int,int> x=Q.front();Q.pop();
		for(int v1:nG[x.first])
			for(int v2:nG[x.second])
				if(c[v1]==c[v2]&&!vis[v1][v2])
				{
					vis[v1][v2]=vis[v2][v1]=1;
					Ans[v1][v2]=Ans[v2][v1]=1;
					Q.emplace(v1,v2);
				}
	}
	for(int i=1,u,v;i<=q;i++)
	{
		scanf("%d%d",&u,&v);
		puts(Ans[u][v]?"YES":"NO");
	}
}
