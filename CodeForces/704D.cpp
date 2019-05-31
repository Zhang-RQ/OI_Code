#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
const int MAXM=2E6+10;
const char str[]="rb";

struct edge_t{
	int v,f,nxt;
}Edge[MAXM];

int SS=0,TT=MAXN-1,S=MAXN-3,T=MAXN-2,cnt_e=1,n,m,r,b;
int head[MAXN],X[MAXN],Y[MAXN],SX[MAXN],SY[MAXN],LX[MAXN],LY[MAXN],Vx[MAXN],Vy[MAXN];
int lvl[MAXN],thead[MAXN],nowS,nowT;
queue<int> q;

void add(int u,int v,int f)
{
	Edge[++cnt_e]=(edge_t){v,f,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f) {add(u,v,f);add(v,u,0);}

int Ceil2(int v){return (v+1)>>1;}

int Floor2(int v){return v>>1;} 

bool bfs()
{
    memset(lvl,0,sizeof lvl);
    q.push(nowS);lvl[nowS]=1;
    while(!q.empty())
    {
		int x=q.front();q.pop();
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(!Edge[i].f||lvl[v])
				continue;
			lvl[v]=lvl[x]+1;
			q.push(v);
		}
    }
	return lvl[nowT]!=0;
}

int dfs(int x,int curf)
{
	if(x==nowT)
		return curf;
	int adf=0;
	for(int &i=thead[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(lvl[v]!=lvl[x]+1||!Edge[i].f)
			continue;
		int mnf=dfs(v,min(curf-adf,Edge[i].f));
		if(!mnf)
			lvl[v]=-1;
		Edge[i].f-=mnf;Edge[i^1].f+=mnf;
		adf+=mnf;
		if(adf==curf)
			break;
	}
	return adf;
}

int Max_Flow()
{
	int Ans=0;
	while(bfs())
		memcpy(thead,head,sizeof head),
		Ans+=dfs(nowS,1<<30);
	return Ans;
}

int main()
{
	int flip=0;
	scanf("%d%d%d%d",&n,&m,&r,&b);
	if(r>b) swap(r,b),flip=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&X[i],&Y[i]);
		Vx[i]=X[i];Vy[i]=Y[i];
	}
	sort(Vx+1,Vx+n+1);sort(Vy+1,Vy+n+1);
	int totx=unique(Vx+1,Vx+n+1)-Vx-1,toty=unique(Vy+1,Vy+n+1)-Vy-1;
	for(int i=1;i<=n;i++)
	{
		X[i]=lower_bound(Vx+1,Vx+1+totx,X[i])-Vx;
		Y[i]=lower_bound(Vy+1,Vy+1+toty,Y[i])-Vy;
		SX[X[i]]++;SY[Y[i]]++;
	}
	for(int i=1;i<=n;i++)
		LX[i]=LY[i]=1<<30;
	for(int i=1,tp,l,d;i<=m;i++)
	{
		scanf("%d%d%d",&tp,&l,&d);
		if(tp==1)
		{
			int _=l;
			l=lower_bound(Vx+1,Vx+totx+1,l)-Vx;
			if(_!=Vx[l])
				continue;
			LX[l]=min(LX[l],d);
		}
		else
		{
			int _=l;
			l=lower_bound(Vy+1,Vy+toty+1,l)-Vy;
			if(_!=Vy[l])
				continue;
			LY[l]=min(LY[l],d);
		}
	}
	int lim=0;
	for(int i=1;i<=totx;i++)
	{
		LX[i]=min(LX[i],SX[i]);
		int L=Ceil2(SX[i]-LX[i]),R=Floor2(SX[i]+LX[i]);
		if(L>R) return puts("-1"),0;
		lim+=L;
		add2(SS,i,L);add2(S,TT,L);add2(S,i,R-L);
	}
	for(int i=1;i<=toty;i++)
	{
		LY[i]=min(LY[i],SY[i]);
		int L=Ceil2(SY[i]-LY[i]),R=Floor2(SY[i]+LY[i]);
		if(L>R) return puts("-1"),0;
		lim+=L;
		add2(SS,T,L);add2(i+totx,TT,L);add2(i+totx,T,R-L);
	}
	vector<int> V;
	for(int i=1;i<=n;i++)
	{
		add2(X[i],Y[i]+totx,1);
		V.push_back(cnt_e^1);
	}
	add2(T,S,1<<30);
	int eid=cnt_e;
	nowS=SS;nowT=TT;
	int tAns=Max_Flow();
	if(tAns<lim)
		return puts("-1"),0;
	int preAns=(1<<30)-Edge[eid^1].f;
	//Edge[eid].f=Edge[eid^1].f=0;
	nowS=S;nowT=T;
	preAns+=Max_Flow();
	printf("%lld\n",1ll*r*preAns+1ll*b*(n-preAns));
	for(int i:V)
	{
		if(Edge[i].f)
			putchar(str[flip^1]);
		else
			putchar(str[flip]);
	}
	puts("");
}
