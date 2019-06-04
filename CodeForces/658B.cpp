#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E5+10;

int n,q,son[MAXN],siz[MAXN],fa[MAXN];
int Ans[MAXN];
vector<int> T[MAXN];

void dfs1(int x,int fa)
{
	siz[x]=1;::fa[x]=fa;
	for(int v:T[x])
		if(v!=fa)
		{
			dfs1(v,x);
			siz[x]+=siz[v];
			if(siz[son[x]]<siz[v])
				son[x]=v;
		}
}

void dfs2(int x,int fa)
{
	if(son[x])
	{
		dfs2(son[x],x);
		Ans[x]=Ans[son[x]];
		while(Ans[x]!=x&&siz[x]-siz[Ans[x]]>siz[x]/2)
			Ans[x]=::fa[Ans[x]];
		for(int v:T[x])
			if(v!=fa&&v!=son[x])
				dfs2(v,x);
	}
	else
		Ans[x]=x;
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2,fa;i<=n;i++)
		scanf("%d",&fa),T[fa].push_back(i);
	dfs1(1,0);dfs2(1,0);
	for(int i=1,x;i<=q;i++)
	{
		scanf("%d",&x);
		printf("%d\n",Ans[x]);
	}
}
