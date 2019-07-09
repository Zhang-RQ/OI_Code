#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=60010;
const int MAXM=2E6+10;
const int INF=1<<30;
const int SS=0;
const int TT=MAXN-1;
const int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

struct edge_t{
	int v,f,c,nxt;
}Edge[MAXM];

char mp[257][257];
int head[MAXN],cnt_e=1,n,m,z,t,vals[81][257][257];
int flw[MAXN],pre[MAXN],pree[MAXN],inq[MAXN];
ll dis[MAXN];
queue<int> q;

int id(int time,int x,int y,int tp){return tp*(t+1)*n*m+time*n*m+(x-1)*m+y;}

void add(int u,int v,int f,int c)
{
	Edge[++cnt_e]=(edge_t){v,f,c,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

bool spfa()
{
	memset(dis,0xcf,sizeof dis);
	dis[SS]=0;flw[SS]=INF;
	q.push(SS);inq[SS]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();inq[x]=0;
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			if(!Edge[i].f)
				continue;
			int v=Edge[i].v;
			if(dis[v]>=dis[x]+Edge[i].c)
				continue;
			dis[v]=dis[x]+Edge[i].c;
			pre[v]=x;pree[v]=i;
			flw[v]=min(flw[x],Edge[i].f);
			if(!inq[v])
				q.push(v),inq[v]=1;
		}
	}
	return dis[TT]!=(ll)0xcfcfcfcfcfcfcfcf;
}

pair<ll,ll> MCMF()
{
	ll Flow=0,Cost=0;
	while(spfa())
	{
		Flow+=flw[TT],Cost+=dis[TT]*flw[TT];
		for(int x=TT;x!=SS;x=pre[x])
			Edge[pree[x]].f-=flw[TT],
			Edge[pree[x]^1].f+=flw[TT];
	}
	return make_pair(Flow,Cost);
}

int main()
{
	int cnts=0;
	scanf("%d%d%d%d",&n,&m,&z,&t);
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	for(int i=1,x,y,p,q,h;i<=z;i++)
	{
		scanf("%d%d%d%d%d",&x,&y,&p,&q,&h);
		for(int c=p;c<q;c++)
			vals[c][x][y]=max(vals[c][x][y],h);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(mp[i][j]=='#')
				continue;
			if(mp[i][j]=='S')
				add2(SS,id(0,i,j,0),1,0),++cnts;
			for(int k=0;k<=t;k++)
			{
				if(k<t)
					add2(id(k,i,j,1),id(k+1,i,j,0),1,0);
				add2(id(k,i,j,0),id(k,i,j,1),1,vals[k][i][j]);
				for(int _=0;_<4;_++)
				{
					int nx=i+mv[_][0],ny=j+mv[_][1];
					if(1<=nx&&nx<=n&&1<=ny&&ny<=m&&mp[nx][ny]!='#')
						add2(id(k,i,j,0),id(k,nx,ny,1),1,0);
				}
			}
			add2(id(t,i,j,1),TT,1,0);
		}
	auto Res=MCMF();assert(Res.first==cnts);
	printf("%lld\n",Res.second);
}
