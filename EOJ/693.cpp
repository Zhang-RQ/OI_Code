#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int INF=1<<30;

int n,q,rl[MAXN],Pnt[MAXN],tot,Ans,stk[MAXN],top;
int dfn[MAXN],dfn_end[MAXN],dft,jmp[MAXN][18],F[MAXN][18],G[MAXN][18];
int f[MAXN],g[MAXN],dep[MAXN],Fa[MAXN],dis[MAXN];
multiset<int> S[MAXN];
vector<int> T[MAXN],vT[MAXN];

void Erase(multiset<int> &s,int v)
{
#ifdef DEBUG
	set<int>::iterator it=s.find(v);
	assert(it!=s.end());
	s.erase(it);
#else
	s.erase(s.find(v));
#endif
}

bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn_end[x];}

int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			x=jmp[x][j];
	if(x==y) return x;
	for(int j=17;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			x=jmp[x][j],y=jmp[y][j];
	return jmp[x][0];
}

int NXT(int x,int y)
{
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>dep[y])
			x=jmp[x][j];
	return x;
}

int JMP(int x,int stp)
{
	for(int j=17;~j;j--)
		if((stp>>j)&1)
			x=jmp[x][j];
	return x;
}

int Query_up(int x,int lim) //query from up
{
	int Ret=-INF;
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>=lim)
			Ret=max(Ret,F[x][j]),
			x=jmp[x][j];
	return Ret;
}

int Query_down(int x,int lim) //query from down
{
	int Ret=-INF;
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>=lim)
			Ret=max(Ret,G[x][j]),
			x=jmp[x][j];
	return Ret;
}

void dfs1(int x,int fa)
{
	Fa[x]=fa;
	dfn[x]=++dft;
	dep[x]=dep[fa]+1;
	jmp[x][0]=fa;
	S[x].insert(0);
	for(int v:T[x])
		if(v!=fa)
			dfs1(v,x),
			S[x].insert(f[v]+1);
	f[x]=*S[x].rbegin();
	dfn_end[x]=dft;
}

void dfs2(int x,int fa)
{
	if(fa)
	{
		Erase(S[fa],f[x]+1);
		g[x]=max(g[fa],*S[fa].rbegin())+1;
		S[fa].insert(f[x]+1);
	}
	for(int v:T[x])
		if(v!=fa)
			dfs2(v,x);
}

void vdfs1(int x,int fa)
{
	dis[x]=rl[x]?0:INF;
	for(int v:vT[x])
		if(v!=fa)
			vdfs1(v,x),dis[x]=min(dis[x],dis[v]+dep[v]-dep[x]);
}

void vdfs2(int x,int fa)
{
	for(int v:vT[x])
		if(v!=fa)
			dis[v]=min(dis[v],dis[x]+dep[v]-dep[x]),vdfs2(v,x);
}

void vdfs3(int x,int fa)
{
	if(fa)
	{
		int M=(dep[x]-dep[fa]+dis[fa]-dis[x])/2,y=JMP(x,min(M,dep[x]-dep[fa]));
		Ans=max(Query_down(x,max(dep[fa]+1,dep[y]))+dis[x]+dep[x],Ans);
		Ans=max(Query_up(y,dep[fa]+1)+dis[fa]-dep[fa],Ans);
	}
	else Ans=max(Ans,dis[x]+g[x]);
	for(int v:vT[x])
		if(v!=fa)
			vdfs3(v,x),Erase(S[x],f[NXT(v,x)]+1);
	Ans=max(Ans,dis[x]+*S[x].rbegin());
	for(int v:vT[x])
		if(v!=fa)
			S[x].insert(f[NXT(v,x)]+1);
}

void solve()
{
	Ans=0;
	for(int i=1;i<=tot;i++)
		rl[Pnt[i]]=1;
	sort(Pnt+1,Pnt+1+tot,[](int x,int y){return dfn[x]<dfn[y];});
	tot=unique(Pnt+1,Pnt+1+tot)-Pnt-1;
	for(int i=tot;i>1;i--)
		Pnt[++tot]=LCA(Pnt[i-1],Pnt[i]);
	sort(Pnt+1,Pnt+1+tot,[](int x,int y){return dfn[x]<dfn[y];});
	tot=unique(Pnt+1,Pnt+1+tot)-Pnt-1;
	top=0;
	for(int i=1;i<=tot;i++)
	{
		while(top&&!inside(stk[top],Pnt[i])) --top;
		if(top) vT[stk[top]].push_back(Pnt[i]);
		stk[++top]=Pnt[i];
	}
	vdfs1(Pnt[1],0);vdfs2(Pnt[1],0);vdfs3(Pnt[1],0);
	for(int i=1;i<=tot;i++)
		rl[Pnt[i]]=0,vT[Pnt[i]].clear();
		
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),T[u].push_back(v),T[v].push_back(u);
	dfs1(1,0);dfs2(1,0);
	for(int i=2;i<=n;i++)
	{
		Erase(S[Fa[i]],f[i]+1);
		F[i][0]=*S[Fa[i]].rbegin()+dep[Fa[i]];
		G[i][0]=*S[Fa[i]].rbegin()-dep[Fa[i]];
		S[Fa[i]].insert(f[i]+1);
	}
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
			jmp[i][j]=jmp[jmp[i][j-1]][j-1],
			F[i][j]=max(F[i][j-1],F[jmp[i][j-1]][j-1]),
			G[i][j]=max(G[i][j-1],G[jmp[i][j-1]][j-1]);
	while(q--)
	{
		int cnt,x;
		tot=0;
		scanf("%d",&cnt);
		while(cnt--)
			scanf("%d",&x),Pnt[++tot]=x;
		solve();
		printf("%d\n",Ans);
	}
}
