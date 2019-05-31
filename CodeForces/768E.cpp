#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3.4E5+10;
const int MAXM=2E6+10;
const int INF=1<<30;

struct edge_t{
	int v,f,nxt;
}Edge[MAXM];

int S=0,T=MAXN-1,n,m,jmp[MAXN][16],pnt[MAXN][16],dep[MAXN];
int cnt_e=1,head[MAXN],thead[MAXN],lvl[MAXN];
vector<pair<int,int> > vT[MAXN];

void add(int u,int v,int f)
{
	Edge[++cnt_e]=(edge_t){v,f,head[u]};
	head[u]=cnt_e;
}

void add2(int u,int v,int f){add(u,v,f);add(v,u,0);}

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
			if(!Edge[i].f||lvl[v])
				continue;
			lvl[v]=lvl[x]+1;
			q.push(v);
		}
	}
	return lvl[T]!=0;
}

int dfs(int x,int curf)
{
	if(x==T)
		return curf;
	int adf=0;
	for(int &i=thead[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(!Edge[i].f||lvl[v]!=lvl[x]+1)
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
		memcpy(thead,head,sizeof thead),
		Ans+=dfs(S,1<<30);
	return Ans;
}

void dfst(int x,int fa)
{
	dep[x]=dep[fa]+1;
	jmp[x][0]=fa;
	for(auto e:vT[x])
	{
		if(e.first!=fa)
		{
			pnt[e.first][0]=m+e.second;
			dfst(e.first,x);
		}
	}
}

void Add(int u,int v,int x)
{
	if(dep[u]<dep[v])
		swap(u,v);
	for(int j=15;~j;j--)
		if(dep[jmp[u][j]]>=dep[v])
			add2(x,pnt[u][j],INF),u=jmp[u][j];
	if(u==v)
		return;
	for(int j=15;~j;j--)
		if(jmp[u][j]!=jmp[v][j])
			add2(x,pnt[u][j],INF),add2(x,pnt[v][j],INF),
			u=jmp[u][j],v=jmp[v][j];
	add2(x,pnt[u][0],INF);add2(x,pnt[v][0],INF);
}

//[1,m] people [m+1,n+m] edges
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),
		vT[u].emplace_back(v,i),
		vT[v].emplace_back(u,i);
	int tot=n+m;
	for(int j=1;j<=15;j++)
		for(int i=1;i<=n;i++)
			pnt[i][j]=++tot;
	dfst(1,0);
	for(int j=1;j<=15;j++)
		for(int i=1;i<=n;i++)
		{
			jmp[i][j]=jmp[jmp[i][j-1]][j-1];
			if(jmp[i][j-1]!=0)
				add2(pnt[i][j],pnt[i][j-1],INF),
				add2(pnt[i][j],pnt[jmp[i][j-1]][j-1],INF);
		}
	for(int i=1,u,v;i<=m;i++)
	{
		add2(S,i,1);
		scanf("%d%d",&u,&v);
		Add(u,v,i);
	}
	for(int i=m+1;i<n+m;i++)
		add2(i,T,1);
	int Ans=Max_Flow();bfs();
	vector<int> peo,gua;
	for(int i=1;i<=m;i++)
		if(!lvl[i])
			peo.push_back(i);
	for(int i=m+1;i<n+m;i++)
		if(lvl[i])
			gua.push_back(i-m);
	printf("%d\n",Ans);
	printf("%d ",peo.size());
	for(int p:peo)
		printf("%d ",p);
	puts("");
	printf("%d ",gua.size());
	for(int p:gua)
		printf("%d ",p);
	puts("");
}
