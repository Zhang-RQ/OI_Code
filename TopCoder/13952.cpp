#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2010;
const int MAXM=5E5+10;
const int INF=1<<30;
const ll INFll=1ll<<60;

struct edge_t{
	int v,f,c,nxt;
}Edge[MAXM];

ll dis[MAXN],Flow,Cost,lim;
int S=0,T=MAXN-1,mp[MAXN][MAXN];
int head[MAXN],cnt_e=1,flw[MAXN],n,ti[MAXN],co[MAXN];
int pre[MAXN],pree[MAXN],q[MAXN*100],inq[MAXN];

void add(int u,int v,int f,int c)
{
	Edge[++cnt_e]=(edge_t){v,f,c,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

void AddE(int u,int v,int f,int c)
{
	if(c>0)
	{
		add2(S,v,f,0);
		add2(u,T,f,0);
		add2(v,u,f,-c);
		Cost+=1ll*f*c;
	}
	else
		add2(u,v,f,c);
}

bool spfa()
{
	for(int i=0;i<MAXN;i++)
		dis[i]=-INFll;
	int hd=1,tl=0;
	inq[S]=1;flw[S]=INF;
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
	return dis[T]!=-INFll;
}

void MCMF()
{
	while(spfa())
	{
		Flow+=flw[T];Cost+=flw[T]*dis[T];
		for(int x=T;x!=S;x=pre[x])
			Edge[pree[x]].f-=flw[T],
			Edge[pree[x]^1].f+=flw[T];
	}
}

bool chk(int Mid)
{
	Flow=Cost=0;cnt_e=1;
	memset(head,0,sizeof head);
	int s=MAXN-3,t=MAXN-2;
	for(int i=1;i<=n;i++)
		AddE(s,i<<1,INF,0),AddE(i<<1|1,t,INF,0);
	AddE(t,s,INF,-Mid);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(mp[j][i])
				AddE(i<<1|1,j<<1,INF,0);
	for(int i=1;i<=n;i++)
		AddE(i<<1,i<<1|1,co[i],ti[i]),
		AddE(i<<1,i<<1|1,INF,0);
	MCMF();
	return Cost<=lim;
}

class Farmville{
public:
	int minTime(vector<string> s,vector<int> time,vector<int> cost,int budget)
	{
		n=s.size();
		int L=0,R=0,Ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				mp[i][j]=s[i-1][j-1]=='1';
		for(int i=1;i<=n;i++)
			ti[i]=time[i-1],co[i]=cost[i-1],R+=ti[i];
		lim=budget;
		while(L<=R)
		{
			int Mid=(L+R)>>1;
			if(chk(Mid))
				Ans=Mid,R=Mid-1;
			else
				L=Mid+1;
		}
		return Ans;
	}
};
