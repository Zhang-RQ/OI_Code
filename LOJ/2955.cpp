#pragma GCC optimize("O2,Ofast,inline,unroll-all-loops,-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,popcnt")
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

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

const int MAXN=1E5+10;
const ll INF=1ll<<42;

struct edge_t{
	int v,nxt;
}Edge[MAXN<<1];

ll F[MAXN][18][2][2],f[MAXN],g[MAXN];
int n,m,head[MAXN],cnt_e,p[MAXN],dep[MAXN],jmp[MAXN][18];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;jmp[x][0]=fa;
	f[x]=p[x];
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs(v,x);
		f[x]+=min(g[v],f[v]);
		g[x]+=f[v];
	}
}

void update(ll f1[2][2],ll f2[2][2],ll res[2][2])
{
	if(f1[0][1]==INF) return memcpy(res,f2,sizeof(ll)*4),void();
	ll tmp[2][2];
	for(int s1=0;s1<=1;s1++)
		for(int s2=0;s2<=1;s2++)
			tmp[s1][s2]=min(f1[s1][0]+f2[0][s2],f1[s1][1]+f2[1][s2]);
	memcpy(res,tmp,sizeof(ll)*4);
}

void Query_rt(int x,ll res[2][2])
{
	if(x==1) return res[0][0]=res[0][1]=res[1][0]=res[1][1]=0,void();
	for(int j=17;~j;j--)
		if(jmp[x][j]!=0)
			update(res,F[x][j],res),x=jmp[x][j];
	assert(x==1);
}

ll Query(int x,int a,int y,int b)//x,y point;a,b state
{
	if(dep[x]<dep[y]) swap(x,y),swap(a,b);
	int _x=x;
	ll tAns=(a?f[x]:g[x])+(b?f[y]:g[y]);
	ll tx[2][2]={{0,INF},{INF,0}},ty[2][2]={{0,INF},{INF,0}},trt[2][2]={{0,INF},{INF,0}},vrt[2];
	for(int j=17;~j;j--)
		if(dep[jmp[x][j]]>=dep[y])
			update(tx,F[x][j],tx),x=jmp[x][j];
	if(x==y)
	{
		Query_rt(y,trt);
		return min(tx[a][b]+trt[b][0],tx[a][b]+trt[b][1])+(a?f[_x]:g[_x]);
	}
	for(int j=17;~j;j--)
		if(jmp[x][j]!=jmp[y][j])
			update(tx,F[x][j],tx),x=jmp[x][j],
			update(ty,F[y][j],ty),y=jmp[y][j];
	Query_rt(jmp[x][0],trt);
	int LCA=jmp[x][0];
	vrt[0]=min(trt[0][0],trt[0][1])+g[LCA]-f[x]-f[y];vrt[1]=min(trt[1][0],trt[1][1])+f[LCA]-min(f[x],g[x])-min(f[y],g[y]);
	ll Ret=INF;
	for(int s1=0;s1<2;s1++)
		for(int s2=0;s2<2;s2++)
			for(int s3=0;s3<2;s3++)
			{
				if(!((s1|s3)&(s2|s3))) continue;
				Ret=min(Ret,tx[a][s1]+ty[b][s2]+vrt[s3]);
			}
	return Ret+tAns;
}

int main()
{
	freopen("defense.in","r",stdin);
	freopen("defense.out","w",stdout);
	int t;
	read(n,m,t);
	for(int i=1;i<=n;i++) read(p[i]);
	for(int i=1,u,v;i<n;i++) read(u,v),add(u,v),add(v,u);
	dfs(1,0);
	for(int x=1;x<=n;x++)
	{
		F[x][0][0][0]=INF;
		F[x][0][1][0]=g[jmp[x][0]]-f[x];
		F[x][0][0][1]=f[jmp[x][0]]-min(g[x],f[x]);
		F[x][0][1][1]=f[jmp[x][0]]-min(g[x],f[x]);
	}
	for(int j=1;j<=17;j++)
		for(int x=1;x<=n;x++)
		{
			jmp[x][j]=jmp[jmp[x][j-1]][j-1];
			update(F[x][j-1],F[jmp[x][j-1]][j-1],F[x][j]);
		}
	for(int _=1,a,x,b,y;_<=m;_++)
	{
		read(a,x,b,y);
		ll res=Query(a,x,b,y);
		if(res>=INF) puts("-1");
		else printf("%lld\n",res);
	}
}