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

const int MAXN=610;
const int MAXM=1E6+10;

int v,e,n,k,dis[MAXN][MAXN],x[MAXN],mat[MAXN<<1];
bool inC[MAXN<<1];


struct __edge{
	int v,nxt;
}Edge[MAXM];

int head[MAXN<<1],cnt_e;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

bool dfs(int x)
{
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(inC[v]) continue;
		inC[v]=1;
		if(!mat[v]||dfs(mat[v])) return mat[v]=x,1;
	}
	return 0;
}

bool check(int Mid)
{
	memset(head,0,sizeof head);cnt_e=0;
	memset(mat,0,sizeof mat);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=v;j++)
			if(dis[x[i]][j]<=Mid)
				add(i,j+n);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		memset(inC,0,sizeof inC);
		cnt+=dfs(i);
		if(cnt>=k) return 1;
	}
	return cnt>=k;
}

int main()
{
	memset(dis,0x3f,sizeof dis);
	scanf("%d%d%d%d",&v,&e,&n,&k);
	if(k>n||k>v) return puts("-1"),0;
	for(int i=1;i<=v;i++) dis[i][i]=0;
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	for(int i=1,u,v,w;i<=e;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		dis[u][v]=min(dis[u][v],w);
		dis[v][u]=min(dis[v][u],w);
	}
	for(int k=1;k<=v;k++)
		for(int i=1;i<=v;i++)
			for(int j=1;j<=v;j++)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	int L=0,R=1731311,Ans=-1;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	printf("%d\n",Ans);
}