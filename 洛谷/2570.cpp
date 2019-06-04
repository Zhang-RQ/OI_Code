#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E4+10;
const int MAXM=1E6+10;
const double EPS=1E-8;

struct edge_t{
	int v,nxt;
	double f;
}Edge[MAXM];

int S=0,T=MAXN-1,k,n,m;
int head[MAXN],thead[MAXN],cnt_e=1,lvl[MAXN];
double p[MAXN],r[MAXN],d[MAXN],s[MAXN],nd[MAXN],fT[MAXN];

void add(int u,int v,double f)
{
	Edge[++cnt_e]=(edge_t){v,head[u],f};
	head[u]=cnt_e;
}

void add2(int u,int v,double f){add(u,v,f);add(v,u,0);}

void clear(){memset(head,0,sizeof head);cnt_e=1;}

bool bfs()
{
	queue<int> q;
	memset(lvl,0,sizeof lvl);
	lvl[S]=1;q.push(S);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(lvl[v]||abs(Edge[i].f)<EPS)
				continue;
			lvl[v]=lvl[x]+1;
			q.push(v);
		}
	}
	return lvl[T]!=0;
}

double dfs(int x,double cuf)
{
	if(x==T)
		return cuf;
	double adf=0;
	for(int &i=thead[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(lvl[v]!=lvl[x]+1||abs(Edge[i].f)<EPS)
			continue;
		double mnf=dfs(v,min(cuf-adf,Edge[i].f));
		if(abs(mnf)<EPS)
			lvl[v]=-1;
		Edge[i].f-=mnf;
		Edge[i^1].f+=mnf;
		adf+=mnf;
		if(abs(cuf-adf)<EPS)
			break;
	}
	return adf;
}

double Max_Flow()
{
	double Ans=0;
	while(bfs())
		memcpy(thead,head,sizeof head),
		Ans+=dfs(S,1E9);
	return Ans;
}

bool Chk(double Mid)
{
	clear();
	for(int i=1;i<=n;i++)
		nd[i]=d[i]+Mid;
	int tot=0,totp=n;
	for(int i=1;i<=n;i++)
		fT[++tot]=nd[i],
		fT[++tot]=r[i];
	sort(fT+1,fT+1+tot);
	double Sum=0;
	for(int i=1;i<=n;i++)
		add2(S,i,p[i]),Sum+=p[i];
	for(int i=1;i<=tot;i++)
	{
		double dur=fT[i]-fT[i-1];
		for(int j=1;j<=m;j++)
		{
			add2(++totp,T,dur*s[j]*j);
			for(int k=1;k<=n;k++)
				if(r[k]<=fT[i-1]&&fT[i]<=nd[k])
					add2(k,totp,dur*s[j]);
		}
	}
	return abs(Sum-Max_Flow())<EPS;
}

void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&p[i],&r[i],&d[i]);
	for(int i=1;i<=m;i++)
		scanf("%lf",&s[i]);
	sort(s+1,s+1+m,greater<double>());
	for(int i=1;i<m;i++)
		s[i]-=s[i+1];
	double L=0,R=5E6;
	for(int T=50;T;T--)
	{
		double Mid=(L+R)*.5;
		if(Chk(Mid))
			R=Mid;
		else
			L=Mid;
	}
	printf("%.10lf\n",L);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
