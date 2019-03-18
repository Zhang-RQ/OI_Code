#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=350;
const int MAXM=1E5+10;

struct edge_t{
	int v,f,c,nxt;
}Edge[MAXM];

int n,m,k,head[MAXN],cnt_e=1,pre[MAXN],pree[MAXN],flw[MAXN];
int G[MAXN][MAXN],dis[MAXN],S=MAXN-2,T=MAXN-1,inq[MAXN];

void add(int u,int v,int f,int c)
{
	Edge[++cnt_e]=(edge_t){v,f,c,head[u]};
	head[u]=cnt_e;
}

bool spfa()
{
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(S);dis[S]=0;flw[S]=1<<30;
	while(!q.empty())
	{
		int x=q.front();q.pop();inq[x]=0;
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(Edge[i].f&&dis[v]>dis[x]+Edge[i].c)
			{
				dis[v]=dis[x]+Edge[i].c;
				pre[v]=x;
				pree[v]=i;
				flw[v]=min(flw[x],Edge[i].f);
				if(!inq[v])
					inq[v]=1,q.push(v);
			}
		}
	}
	return dis[T]!=0x3f3f3f3f;
}

int MCMF()
{
	int Ret=0,Flw=0;
	while(spfa())
	{
		Flw+=flw[T];
		Ret+=dis[T]*flw[T];
		int x=T;
		while(x!=S)
		{
			Edge[pree[x]].f-=flw[T];
			Edge[pree[x]^1].f+=flw[T];
			x=pre[x];
		}
	}
	return Ret;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	memset(G,0x3f,sizeof G);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		G[u][v]=G[v][u]=min(G[u][v],w);
	}
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				if(k<=max(i,j))
					G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	for(int i=0;i<=n;i++)//这么建图应该是因为有完美匹配才能这么玩
		for(int j=i+1;j<=n;j++)
			add(i*2,j*2+1,1,G[i][j]),
			add(j*2+1,2*i,0,-G[i][j]);
	for(int i=0;i<=n;i++)
	{
		if(i==0) add(S,2*i,k,0),add(2*i,S,0,0);
		else add(S,2*i,1,0),add(2*i,S,0,0);
		add(2*i+1,T,1,0);
		add(T,2*i+1,0,0);
	}
	printf("%d\n",MCMF());
}
