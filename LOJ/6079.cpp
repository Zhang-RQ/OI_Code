#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3010;
const int MAXM=1E6+10;
const int INF=1<<30;
const ll INFll=1ll<<60;

struct edge_t{
	int v,f,c,nxt;
}Edge[MAXM];

int S,T=MAXN-1,s[MAXN],e[MAXN],head[MAXN],cnt_e=1;
int n,k,ms,me,pre[MAXN],pree[MAXN],inq[MAXN],id[MAXN];
ll dis[MAXN],flw[MAXN];
queue<int> q;

void add(int u,int v,int f,int c)
{
	Edge[++cnt_e]=(edge_t){v,f,c,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f,int c){add(u,v,f,c);add(v,u,0,-c);}

bool spfa()
{
	memset(dis,0xcf,sizeof dis);inq[S]=1;
	dis[S]=0;q.push(S);flw[S]=((ll)INF)<<20;
	while(!q.empty())
	{
		int x=q.front();q.pop();inq[x]=0;
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(!Edge[i].f||dis[v]>=dis[x]+Edge[i].c)
				continue;
			pre[v]=x;pree[v]=i;
			dis[v]=dis[x]+Edge[i].c;
			flw[v]=min(flw[x],(ll)Edge[i].f);
			if(!inq[v])
				q.push(v),inq[v]=1;
		}
	}
	return dis[T]!=(ll)0xcfcfcfcfcfcfcfcf;
}

pair<ll,ll> MCMF()
{
	ll Flow=0,Cost=0;
	while(spfa())
	{
		Flow+=flw[T];Cost+=dis[T]*flw[T];
		int x=T;
		while(x!=S)
		{
			Edge[pree[x]].f-=flw[T];
			Edge[pree[x]^1].f+=flw[T];
			x=pre[x];
		}
	}
	return make_pair(Flow,Cost);
}

int main()
{
	scanf("%d%d%d%d",&n,&k,&ms,&me);
	ll Ans=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]),Ans+=s[i];
	for(int i=1;i<=n;i++)
		scanf("%d",&e[i]);
	for(int i=2;i<=2*(n-k+1);i+=2)
	{
		add2(i,i-1,INF,0);//yi
		add2(i,i+1,INF,0);//zi
		add2(S,i,k-ms-me,0);
	}
	for(int i=1;i<=k;i++)
	{
		id[i]=cnt_e+1;
		if(2*i+1<=2*(n-k+1))
			add2(1,2*i+1,1,e[i]-s[i]);//x1...xk
		else
			add2(1,2*(n-k+1)+1,1,e[i]-s[i]);
	}
	add2(S,1,me,0);
	for(int i=3;i<=2*(n-k+1);i+=2)
	{
		id[k+(i>>1)]=cnt_e+1;
		if(2*k+i<=2*(n-k+1))
			add2(i,2*k+i,1,e[k+(i>>1)]-s[k+(i>>1)]);//x k+(i/2)
		else
			add2(i,2*(n-k+1)+1,1,e[k+(i>>1)]-s[k+(i>>1)]);
		add2(i,T,k-ms-me,0);
	}
	add2(2*(n-k+1)+1,T,k-ms,0);
	pair<ll,ll> Res=MCMF();
	printf("%lld\n",Res.second+Ans);
	for(int i=1;i<=n;i++)
		putchar("ES"[Edge[id[i]].f]);
}
