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

const int MAXN=12;
const int INF=0x3f3f3f3f;

int g[MAXN][MAXN],f[1<<MAXN][MAXN][MAXN],Cnt[1<<MAXN],n,m;

int F(int s,int x,int d)
{
	if(Cnt[s]==1) return 0;
	if(~f[s][x][d]) return f[s][x][d];
	int Ret=INF,S=s;s^=1<<x;
	for(int t=s;t;t=(t-1)&s)
		for(int v=0;v<n;v++)
			if(((t>>v)&1)&&g[x][v]!=INF)
				Ret=min(Ret,F(S^t,x,d)+F(t,v,d+1)+g[x][v]*(d+1));
	return f[S][x][d]=Ret;
}

int main()
{
	memset(g,0x3f,sizeof g);
	scanf("%d%d",&n,&m);
	for(int s=1;s<1<<n;s++)
		Cnt[s]=Cnt[s^(s&(-s))]+1;
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		--u;--v;
		g[u][v]=min(g[u][v],w);
		g[v][u]=min(g[v][u],w);
	}
	int Ans=INF;memset(f,-1,sizeof f);
	for(int i=0;i<n;i++)
		Ans=min(Ans,F((1<<n)-1,i,0));
	printf("%d\n",Ans);
}