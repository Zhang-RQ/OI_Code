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

const int MAXN=105;

int n,m,v[MAXN],g[MAXN][MAXN],k;
int f[MAXN][1<<13];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	memset(g,0x3f,sizeof g);memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g[u][v]=min(g[u][v],w);
	}
	for(int i=1;i<=n;i++)
		f[i][1<<v[i]]=0;
	for(int s=1;s<1<<k;s++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(g[i][j]!=0x3f3f3f3f&&((~s>>v[j])&1))
					f[j][s|(1<<v[j])]=min(f[j][s|(1<<v[j])],f[i][s]+g[i][j]);
	int Ans=0x3f3f3f3f,ful=(1<<k)-1;
	for(int i=1;i<=n;i++)
		Ans=min(Ans,f[i][ful]);
	if(Ans>=0x3f3f3f3f) puts("Ushio!");
	else printf("%d\n",Ans);
}