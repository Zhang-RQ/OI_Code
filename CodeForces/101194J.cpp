#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;
const int MAXM=5E5+10;

struct edge_t{
	int v,f,c,nxt;
}Edge[MAXM];

int S=0,T=MAXN-1,TST,n,m,E;
int head[MAXN],cnt_e=1,dis[MAXN],flw[MAXN],Es[310][310];
int pre[MAXN],pree[MAXN],q[MAXN*100],inq[MAXN],costR[310][310],costC[310][310];

void add(int u,int v,int f,int c)
{
	Edge[++cnt_e]=(edge_t){v,f,c,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

bool spfa()
{
	memset(dis,0xcf,sizeof dis);
	int hd=1,tl=0;
	inq[S]=1;flw[S]=1<<30;
	q[++tl]=S;dis[S]=0;
	while(hd<=tl)
	{
		int x=q[hd++];inq[x]=0;
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			if(!Edge[i].f)
				continue;
			int v=Edge[i].v;
			if(dis[v]<dis[x]+Edge[i].c)
			{
				flw[v]=min(flw[x],Edge[i].f);
				pre[v]=x;pree[v]=i;
				dis[v]=dis[x]+Edge[i].c;
				if(!inq[v])
					inq[v]=1,q[++tl]=v;
			}
		}
	}
	return dis[T]!=(int)0xcfcfcfcf;
}

pair<int,int> MCMF()
{
	int Flow=0,Cost=0;
	while(spfa())
	{
		Flow+=flw[T];Cost+=flw[T]*dis[T];
		for(int x=T;x!=S;x=pre[x])
			Edge[pree[x]].f-=flw[T],
			Edge[pree[x]^1].f+=flw[T];
	}
	return make_pair(Flow,Cost);
}

void solve()
{
	memset(Es,0,sizeof Es);
	memset(head,0,sizeof head);
	cnt_e=1;
	scanf("%d%d",&n,&m);
	auto id=[&](int x,int y){return (x-1)*m+y;};
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			scanf("%d",&costC[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&costR[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if((i+j)&1)
			{
				if(j>1)
					add2(2*id(i,j)-1,2*id(i,j-1),1,costC[i][j-1]);
				if(j<m)
					add2(2*id(i,j)-1,2*id(i,j+1),1,costC[i][j]);
			}
			else
			{
				if(i>1)
					add2(2*id(i,j)-1,2*id(i-1,j),1,costR[i-1][j]);
				if(i<n)
					add2(2*id(i,j)-1,2*id(i+1,j),1,costR[i][j]);
			}
		}
	scanf("%d",&E);
	for(int i=1,x,y;i<=E;i++)
		scanf("%d%d",&x,&y),
		Es[x][y]=1;
	for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++)
		{
			if(!Es[x][y])
				add2(2*id(x,y)-1,2*id(x,y),1,0);
			add2(S,2*id(x,y)-1,1,0);add2(2*id(x,y),T,1,0);
		}
	pair<int,int> res=MCMF();
	if(res.first!=n*m)
		printf("Case #%d: Impossible\n",++TST);
	else
		printf("Case #%d: %d\n",++TST,res.second);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
