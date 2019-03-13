#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;
const int MAXM=1E5+10;
const int INF=1<<30;

struct edge_t{
	int v,f,nxt;
}Edge[MAXM];

int cnt_e=1,head[MAXN],n,a1,a2,an,b1,b2,bn;
int lvl[MAXN],S=0,T=MAXN-1,cnt;
char mp[100][100];
queue<int> q;

void add(int u,int v,int f)
{
	Edge[++cnt_e]=(edge_t){v,f,head[u]};
	head[u]=cnt_e;
}

bool bfs()
{
	memset(lvl,0,sizeof lvl);
	q.push(S);lvl[S]=1;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=Edge[i].nxt)
		{
			int v=Edge[i].v;
			if(!Edge[i].f||lvl[v]) continue;
			lvl[v]=lvl[x]+1;
			q.push(v);
		}
	}
	return lvl[T]!=0;
}

int dfs(int x,int curf)
{
	if(x==T) return curf;
	int adf=0;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(lvl[v]!=lvl[x]+1||!Edge[i].f) continue;
		int mnf=dfs(v,min(curf-adf,Edge[i].f));
		if(!mnf) lvl[v]=0;
		adf+=mnf;
		Edge[i].f-=mnf;
		Edge[i^1].f+=mnf;
	}
	return adf;
}

bool chk()
{
	cnt_e=1;memset(head,0,sizeof head);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(mp[i][j]=='N')
				add(i,j,INF),add(j,i,0);
			else if(mp[i][j]=='O')
				add(i,j,1),add(j,i,0);
	add(S,a1,an);add(a1,S,0);
	add(a2,T,an);add(T,a2,0);
	add(S,b1,bn);add(b1,S,0);
	add(b2,T,bn);add(T,b2,0);
	int F=0;
	while(bfs())
		F+=dfs(S,INF);
	return F==an+bn;
}

void solve()
{
	if(!(~scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn))) exit(0);
	++a1;++a2;++b1;++b2;
	for(int i=1;i<=n;i++)
		scanf("%s",mp[i]+1);
	if(chk()&&(swap(b1,b2),chk())) puts("Yes");
	else puts("No");
}

int main()
{
	while(1)
		solve();
}
