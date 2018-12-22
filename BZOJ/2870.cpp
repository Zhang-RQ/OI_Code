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
#include<ctime>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

#define fi first
#define se second

const int MAXN=2E5+10;

ll Ans;
bool vis[MAXN];
vector<int> son[MAXN];
pair<int,int> st[2][MAXN];
int n,tn,val[MAXN],siz[MAXN],mx_rt,rt,Fa[MAXN],tot[2];

struct _edge{int v,w,nxt;};

struct Graph{
	int head[MAXN],cnt_e;
	_edge Edge[MAXN<<1];

	int& operator () (int i) {return head[i];}
	_edge& operator [] (int i) {return Edge[i];}

	void add(int u,int v,int w)
	{
		Edge[++cnt_e].w=w;
		Edge[cnt_e].v=v;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}
}G,T;

void dfsi(int x,int fa)
{
	for(int i=G(x);i;i=G[i].nxt)
	{
		int v=G[i].v;
		if(v==fa) continue;
		dfsi(v,x);son[x].push_back(v);
	}
}

bool chk(int x,int v){return ((Fa[x]==v&&vis[x])||(Fa[x]!=v&&vis[v]));}

void find_rt(int x,int fa,int sz)
{
	siz[x]=1;
	for(int i=T(x);i;i=T[i].nxt)
	{
		int v=T[i].v;
		if(v==fa||chk(x,v)) continue;
		find_rt(v,x,sz);siz[x]+=siz[v];
	}
	int mx=max(siz[x],sz-siz[x]);
	if(!vis[x]&&Fa[x]&&mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs(int x,int fa,bool f,int dis,int Val)
{
	st[f][++tot[f]]=make_pair(Val,dis);
	for(int i=T(x);i;i=T[i].nxt)
	{
		int v=T[i].v;
		if(v==fa||chk(x,v)) continue;
		dfs(v,x,f,dis+T[i].w,min(Val,val[v]));
	}
}

void solve(int x)
{
	vis[x]=1;tot[0]=tot[1]=0;
	if(Fa[x]) dfs(Fa[x],x,0,x<=tn,val[Fa[x]]);
	dfs(x,Fa[x],1,0,val[x]);
	sort(st[0]+1,st[0]+1+tot[0]);sort(st[1]+1,st[1]+1+tot[1]);
	int ptr=tot[1]+1,Mxd=-1234566;
	for(int i=tot[0];i>=1;i--)
	{
		while(ptr>1&&st[1][ptr-1].fi>=st[0][i].fi) Mxd=max(Mxd,st[1][--ptr].se);
		Ans=max(Ans,1ll*st[0][i].fi*(Mxd+st[0][i].se+1));
	}
	ptr=tot[0]+1,Mxd=-1234566;
	for(int i=tot[1];i>=1;i--)
	{
		while(ptr>1&&st[0][ptr-1].fi>=st[1][i].fi) Mxd=max(Mxd,st[0][--ptr].se);
		Ans=max(Ans,1ll*st[1][i].fi*(Mxd+st[1][i].se+1));
	}
	if(Fa[x])
	{
		mx_rt=1<<30,rt=0;
		find_rt(Fa[x],x,siz[Fa[x]]);
		if(rt) solve(rt);
	}
	mx_rt=1<<30,rt=0;
	find_rt(x,0,siz[x]);
	if(rt) solve(rt);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),G.add(u,v,0),G.add(v,u,0);
	if(n==1) return printf("%d\n",val[1]),0;
	dfsi(1,0);tn=n;
	for(int i=1;i<=n;i++)
	{
		if(son[i].size()<=2)
			for(int j=0;j<(signed)son[i].size();j++)
				T.add(i,son[i][j],son[i][j]<=tn),T.add(son[i][j],i,son[i][j]<=tn),Fa[son[i][j]]=i;
		else
		{
			int nl=++n,nr=++n;
			val[nl]=val[nr]=val[i];
			Fa[nl]=Fa[nr]=i;
			T.add(i,nl,0),T.add(nl,i,0);
			T.add(i,nr,0);T.add(nr,i,0);
			for(int j=0;j<(signed)son[i].size();j++)
				if(j&1) son[nr].push_back(son[i][j]);
				else son[nl].push_back(son[i][j]);
		}
	}
	mx_rt=1<<30,rt=0;
	find_rt(1,0,n);
	solve(rt);
	printf("%lld\n",Ans);
}	