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

const int MAXN=5E5+10;
const int MAXM=1E6+10;
const int INF=1<<30;

struct __edge{
	int nxt,v,w;
}Edge[MAXM];

int head[MAXN],cnt_e,idx[MAXN],n,k;
bool siz[MAXN],chk[MAXN];
ll f[2][MAXN],g[MAXN],Ans[MAXN],h[MAXN];

inline void add(int u,int v,int w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
}

void dfs1(int x,int fa)
{
	siz[x]=chk[x];
	f[0][x]=f[1][x]=-INF;
	if(siz[x]) f[0][x]=0;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs1(v,x);
		if(siz[v]) Ans[1]+=2*Edge[i].w;
		if(f[0][v]+Edge[i].w>f[0][x]) f[1][x]=f[0][x],f[0][x]=f[0][v]+Edge[i].w,idx[x]=v;
		else if(f[0][v]+Edge[i].w>f[1][x]) f[1][x]=f[0][v]+Edge[i].w;
		siz[x]|=siz[v];
	}
}

void dfs2(int x,int fa,int fa_dis)
{
	h[x]=h[fa]+fa_dis;
	if(idx[fa]==x) h[x]=max(h[x],f[1][fa]+fa_dis);
	else h[x]=max(h[x],f[0][fa]+fa_dis);
	if(fa) Ans[x]=Ans[fa]+(siz[x]?0:2*fa_dis);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs2(v,x,Edge[i].w);
	}
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	for(int i=1,x;i<=k;i++) scanf("%d",&x),chk[x]=1;
	dfs1(1,0);dfs2(1,0,0);
	for(int i=1;i<=n;i++) printf("%lld\n",Ans[i]-max(f[0][i],h[i]));
}