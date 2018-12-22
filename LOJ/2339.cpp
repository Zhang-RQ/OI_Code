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

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E5+10;
const ll INF=1ll<<60;

struct _edge{int v,nxt;ll w;};

struct Graph{
	_edge Edge[MAXN<<1];
	int head[MAXN],cnt_e;

	int& operator () (int i) {return head[i];}
	_edge& operator [] (int i) {return Edge[i];}

	void add(int u,int v,ll w)
	{
		Edge[++cnt_e].w=w;
		Edge[cnt_e].v=v;
		Edge[cnt_e].nxt=head[u];
		head[u]=cnt_e;
	}
}T1,T2,T3,T1t;

struct Tree{
	Graph* t;
	int pos[MAXN],st[MAXN][20],lca[MAXN][20],dft,dep[MAXN],lg2[MAXN],dfn[MAXN],dft2,siz[MAXN];
	ll dis[MAXN];

	Tree(Graph* TP=nullptr) {t=TP;}

	bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;}

	void dfs(int x,int fa)
	{
		st[pos[x]=++dft][0]=dep[x];
		lca[dft][0]=x;siz[x]=1;dfn[x]=++dft2;
		for(int i=(*t)(x);i;i=(*t)[i].nxt)
		{
			int v=(*t)[i].v;
			if(v==fa) continue;
			dis[v]=dis[x]+(*t)[i].w;dep[v]=dep[x]+1;
			dfs(v,x);siz[x]+=siz[v];
			st[++dft][0]=dep[x];
			lca[dft][0]=x;
		}
	}

	void init()
	{
		dfs(1,0);
		for(int i=2;i<=dft;i++)
			lg2[i]=lg2[i>>1]+1;
		for(int j=1;j<=lg2[dft];j++)
			for(int i=1;i+(1<<j)-1<=dft;i++)
				if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
					st[i][j]=st[i][j-1],lca[i][j]=lca[i][j-1];
				else st[i][j]=st[i+(1<<(j-1))][j-1],lca[i][j]=lca[i+(1<<(j-1))][j-1];
	}

	int LCA(int x,int y)
	{
		x=pos[x],y=pos[y];
		if(x>y) swap(x,y);
		int len=lg2[y-x+1];
		return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
	}

	ll DIS(int x,int y)
	{
		return dis[x]+dis[y]-2*dis[LCA(x,y)];
	}
}t1(&T1),t2(&T2),t3(&T3);

vector<int> son[MAXN];
int n,tn,Fa[MAXN],vis[MAXN],siz[MAXN],mx_rt,rt;
ll dv1[MAXN],Ans=-INF,dis[MAXN];

bool chk(int x,int v){return (v==Fa[x]&&vis[x])||(v!=Fa[x]&&vis[v]);}

ll Dis(int x,int y){return x&&y?t3.DIS(x,y)+dv1[x]+t2.dis[x]+dv1[y]+t2.dis[y]:-INF/2*((!x)+(!y));}

struct dat{
	int p1,p2,q1,q2;
	ll dp,dq;

	dat(){dp=dq=-INF;p1=p2=q1=q2=0;}

	void updatep(int x,int y){ll d=Dis(x,y);if(d>dp) dp=d,p1=x,p2=y;}

	void updateq(int x,int y){ll d=Dis(x,y);if(d>dq) dq=d,q1=x,q2=y;}

	friend dat operator + (const dat &lhs,const dat &rhs)
	{
		dat ret;

		if(lhs.dp>rhs.dp)  ret.dp=lhs.dp,ret.p1=lhs.p1,ret.p2=lhs.p2;
		else  ret.dp=rhs.dp,ret.p1=rhs.p1,ret.p2=rhs.p2;

		if(lhs.dq>rhs.dq)  ret.dq=lhs.dq,ret.q1=lhs.q1,ret.q2=lhs.q2;
		else  ret.dq=rhs.dq,ret.q1=rhs.q1,ret.q2=rhs.q2;

		ret.updatep(lhs.p1,rhs.p1);ret.updatep(lhs.p2,rhs.p1);
		ret.updatep(lhs.p1,rhs.p2);ret.updatep(lhs.p2,rhs.p2);

		ret.updateq(lhs.q1,rhs.q1);ret.updateq(lhs.q2,rhs.q1);
		ret.updateq(lhs.q1,rhs.q2);ret.updateq(lhs.q2,rhs.q2);

		return ret;
	}
}f[MAXN];

namespace Vtree{
	int pnt[MAXN],tot,rl[MAXN],stk[MAXN],top,col[MAXN];
	vector<int> g[MAXN];

	void build()
	{
		sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return t2.dfn[x]<t2.dfn[y];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		int ntot=tot;
		for(int i=2;i<=ntot;i++)
			pnt[++tot]=t2.LCA(pnt[i-1],pnt[i]);
		sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return t2.dfn[x]<t2.dfn[y];});
		tot=unique(pnt+1,pnt+1+tot)-pnt-1;
		stk[top=1]=pnt[1];
		for(int i=2;i<=tot;i++)
		{
			while(!t2.inside(stk[top],pnt[i])) --top;
			g[stk[top]].push_back(pnt[i]);
			stk[++top]=pnt[i];
		}
	}

	void dfs(int x)
	{
		ll tAns=-INF;
		f[x]=dat();
		if(rl[x])
		{
			if(col[x]) f[x].q1=x;
			else f[x].p1=x;
		}
		for(int v:g[x])
		{
			dfs(v);
			tAns=max(tAns,Dis(f[x].p1,f[v].q1));tAns=max(tAns,Dis(f[x].p1,f[v].q2));
			tAns=max(tAns,Dis(f[x].p2,f[v].q1));tAns=max(tAns,Dis(f[x].p2,f[v].q2));
			tAns=max(tAns,Dis(f[x].q1,f[v].p1));tAns=max(tAns,Dis(f[x].q1,f[v].p2));
			tAns=max(tAns,Dis(f[x].q2,f[v].p1));tAns=max(tAns,Dis(f[x].q2,f[v].p2));
			f[x]=f[x]+f[v];
		}
		Ans=max(Ans,tAns-2*t2.dis[x]);
	}

	void solve()
	{
		build();
		dfs(pnt[1]);
		for(int i=1;i<=tot;i++)
			g[pnt[i]].clear(),col[pnt[i]]=rl[pnt[i]]=0;
	}
}

using Vtree::col;using Vtree::pnt;using Vtree::tot;using Vtree::rl;

void dfsi(int x,int fa)
{
	for(int i=T1(x);i;i=T1[i].nxt)
	{
		int v=T1[i].v;
		if(v==fa) continue;
		dfsi(v,x);
		son[x].push_back(v);
		dis[v]=T1[i].w;
	}
}

void build_t()
{
	dfsi(1,0);tn=n;
	for(int i=1;i<=n;i++)
	{
		if(son[i].size()<=2)
			for(int v:son[i])
				T1t.add(i,v,dis[v]),T1t.add(v,i,dis[v]),Fa[v]=i;
		else
		{
			int nl=++n,nr=++n,f=0;
			Fa[nl]=Fa[nr]=i;
			T1t.add(i,nl,0),T1t.add(nl,i,0);
			T1t.add(i,nr,0),T1t.add(nr,i,0);
			for(int v:son[i])
				if(f) son[nr].push_back(v),f^=1;
				else son[nl].push_back(v),f^=1;
		}
	}
}

void dfs(int x,int fa,int co,ll d)
{
	if(x<=tn)
	{
		dv1[x]=d;
		pnt[++tot]=x;
		col[x]=co;rl[x]=1;
	}
	for(int i=T1t(x);i;i=T1t[i].nxt)
	{
		int v=T1t[i].v;
		if(v==fa||chk(x,v)) continue;
		dfs(v,x,co,d+T1t[i].w);
	}
}

void find_rt(int x,int fa,int sz)
{
	siz[x]=1;
	for(int i=T1t(x);i;i=T1t[i].nxt)
	{
		int v=T1t[i].v;
		if(v==fa||chk(x,v)) continue;
		find_rt(v,x,sz);siz[x]+=siz[v];
	}
	int mx=max(siz[x],sz-siz[x]);
	if(Fa[x]&&!vis[x]&&mx<mx_rt) mx_rt=mx,rt=x;
}

void solve(int x)
{
	vis[x]=1;tot=0;
	dfs(Fa[x],x,0,dis[x]);
	dfs(x,0,1,0);
	Vtree::solve();
	mx_rt=1<<30;rt=0;
	find_rt(Fa[x],x,siz[Fa[x]]);
	if(rt) solve(rt);
	mx_rt=1<<30;rt=0;
	find_rt(x,0,siz[x]);
	if(rt) solve(rt);
}

int main()
{
	scanf("%d",&n);
	ll W;
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d%lld",&u,&v,&W);
		T1.add(u,v,W);T1.add(v,u,W);
	}
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d%lld",&u,&v,&W);
		T2.add(u,v,W);T2.add(v,u,W);
	}
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d%lld",&u,&v,&W);
		T3.add(u,v,W);T3.add(v,u,W);
	}
	t1.init();t2.init();t3.init();
	build_t();
	mx_rt=1<<30;
	find_rt(1,0,n);
	solve(rt);
	printf("%lld\n",Ans);
}