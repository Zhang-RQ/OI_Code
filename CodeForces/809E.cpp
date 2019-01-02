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

const int MAXN=2E5+10;
const int P=1E9+7;

struct _edge{int v,nxt;}Edge[MAXN];

int rl[MAXN],pnt[MAXN],tot,stk[MAXN],top,dfn[MAXN],dft2,siz[MAXN],n,a[MAXN],rev[MAXN];
int head[MAXN],cnt_e,lg2[MAXN<<1],st[MAXN<<1][20],lca[MAXN<<1][20],dft,dep[MAXN],pos[MAXN];
ll f[MAXN],f1[MAXN],h[MAXN],Ans,s[MAXN],Res;
vector<int> g[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret; 
}

namespace sieve{
	bool vis[MAXN];
	int pri[MAXN],tot,phi[MAXN],mu[MAXN];

	void sieve()
	{
		phi[1]=1;mu[1]=1;
		for(int i=2;i<=n;i++)
		{
			if(!vis[i]) pri[++tot]=i,phi[i]=i-1,mu[i]=-1;
			for(int j=1;j<=tot&&pri[j]*i<=n;j++)
			{
				vis[i*pri[j]]=1;
				if(i%pri[j]) phi[i*pri[j]]=phi[i]*(pri[j]-1),mu[i*pri[j]]=-mu[i];
				else {phi[i*pri[j]]=phi[i]*pri[j];mu[i*pri[j]]=0;break;}
			}
		}
	}
}

using sieve::phi;using sieve::mu;

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

bool inside(int x,int y){return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;}

void dfsi(int x,int fa)
{
	st[pos[x]=++dft][0]=dep[x];
	lca[dft][0]=x;dfn[x]=++dft2;siz[x]=1;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dep[v]=dep[x]+1;
		dfsi(v,x);siz[x]+=siz[v];
		st[++dft][0]=dep[x];
		lca[dft][0]=x;
	}
}

void init()
{
	for(int i=2;i<=dft;i++) lg2[i]=lg2[i>>1]+1;
	for(int j=1;j<=lg2[dft];j++)
		for(int i=1;i+(1<<j)-1<=dft;i++)
			if(st[i][j-1]<st[i+(1<<(j-1))][j-1])
				st[i][j]=st[i][j-1],lca[i][j]=lca[i][j-1];
			else st[i][j]=st[i+(1<<(j-1))][j-1],lca[i][j]=lca[i+(1<<(j-1))][j-1];
}

int LCA(int x,int y)
{
	x=pos[x];y=pos[y];
	if(x>y) swap(x,y);
	int len=lg2[y-x+1];
	return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}

void vbuild()
{
	sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
	tot=unique(pnt+1,pnt+1+tot)-pnt-1;
	for(int i=tot;i>1;i--) pnt[++tot]=LCA(pnt[i],pnt[i-1]);
	sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dfn[x]<dfn[y];});
	tot=unique(pnt+1,pnt+1+tot)-pnt-1;
	stk[top=1]=pnt[1];
	for(int i=2;i<=tot;i++)
	{
		while(!inside(stk[top],pnt[i])) --top;
		g[stk[top]].push_back(pnt[i]);
		stk[++top]=pnt[i];
	}
}

void dfs(int x)
{
	f[x]=f1[x]=0;
	if(rl[x])
	{
		f[x]=1ll*phi[a[x]]*dep[x]%P;
		f1[x]=phi[a[x]];
	}
	for(int v:g[x])
	{
		dfs(v);
		Res+=(f[x]*f1[v]%P+f[v]*f1[x]%P-2ll*dep[x]*f1[x]%P*f1[v]%P)%P;
		(f[x]+=f[v])%=P;
		(f1[x]+=f1[v])%=P;
	}
}

void solve(int d)
{
	Res=tot=0;
	for(int i=d;i<=n;i+=d) pnt[++tot]=rev[i],rl[rev[i]]=1;
	vbuild();dfs(pnt[1]);h[d]=Res;
	for(int i=1;i<=tot;i++) g[pnt[i]].clear(),rl[pnt[i]]=0;
}

int main()
{
	scanf("%d",&n);sieve::sieve();
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),rev[a[i]]=i;
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfsi(1,0);init();
	for(int i=1;i<=n;i++) solve(i);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			(s[i]+=h[j]*mu[j/i]%P)%=P;
	for(int i=1;i<=n;i++)
		Ans+=i*ksm(phi[i],P-2)%P*s[i]%P;
	Ans=(Ans%P+P)%P;
	printf("%lld\n",ksm(1ll*n*(n-1)%P,P-2)*Ans*2%P);
}