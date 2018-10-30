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

int n,m,dep[MAXN],fa[MAXN],anc[MAXN],ance[MAXN],jmp[MAXN][19];
vector<pair<int,int> > g[MAXN];
vector<tuple<int,int,int> > es;
ll Ans[MAXN],c[MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	anc[x]=fa;jmp[x][0]=fa;
	for(auto e:g[x])
		if(e.first!=fa)
			dfs(e.first,x),Ans[e.second]=c[e.first],c[x]-=c[e.first],ance[e.first]=e.second;
}

int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=18;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=18;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int get_dis(int x,int y) {return dep[x]+dep[y]-2*dep[LCA(x,y)]+1;}

void change_val(int x,int dlt)
{
	int ff=-1;
	while(x)
	{
		Ans[ance[x]]+=dlt*ff;
		ff*=-1;x=anc[x];
	}
}

void Output()
{
	puts("YES");
	for(int i=1;i<=m;i++)
		printf("%lld\n",Ans[i]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]),fa[i]=i;
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		int U=find(u),V=find(v);
		if(U!=V)
		{
			g[u].push_back({v,i});g[v].push_back({u,i});
			fa[U]=V;
		}
		else es.push_back(tuple<int,int,int>(u,v,i));
	}
	dfs(1,0);
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
	if(c[1]==0) return Output(),0;
	if(c[1]&1) return puts("NO"),0;
	bool f=0;
	for(auto e:es)
		if(get_dis(get<0>(e),get<1>(e))&1)
		{
			if(!(dep[get<0>(e)]&1)) c[1]=-c[1];
			f=1;Ans[get<2>(e)]=c[1]/2;
			change_val(get<0>(e),c[1]/2);
			change_val(get<1>(e),c[1]/2);
			break;
		}
	if(f) Output();
	else puts("NO");
}