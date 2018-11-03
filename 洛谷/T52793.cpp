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

const int mv[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

const int MAXN=1E3+10;

int fa[MAXN*MAXN],id[MAXN][MAXN],tot,n,m;
int mp[MAXN][MAXN],kong[MAXN][MAXN];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void merge(int x,int y)
{
	x=find(x);y=find(y);
	fa[x]=y;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mp[i][j]),id[i][j]=++tot;
	for(int i=1;i<=tot;i++) fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!mp[i][j])
			{
				bool f=1;
				for(int k=0;k<8;k++)
					f&=!mp[i+mv[k][0]][j+mv[k][1]];
				kong[i][j]=f;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(kong[i][j])
			{
				for(int k=0;k<8;k++)
				{
					int x=i+mv[k][0],y=j+mv[k][1];
					if(kong[x][y]) merge(id[i][j],id[x][y]);
				}
			}
	int Ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(kong[i][j])
				Ans+=fa[id[i][j]]==id[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!kong[i][j]&&!mp[i][j])
			{
				bool f=1;
				for(int k=0;k<8;k++)
					f&=!kong[i+mv[k][0]][j+mv[k][1]];
				Ans+=f;	
			}
	printf("%d\n",Ans);
}