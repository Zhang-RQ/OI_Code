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

const int MAXN=1E6+10;
const int MAXM=1E6+10;

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
}

using namespace FastIO;

struct __edge{
	int v,nxt;
}Edge[MAXM<<1];

int head[MAXN],cnt_e,siz[MAXN],dep[MAXN],f[2][MAXN],p[MAXN],g[MAXN],n;
int ok[MAXN],mxp[MAXN];
ll Ans[MAXN];

void add(int u,int v)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	head[u]=cnt_e;
}

void dfs1(int x,int fa,int dep)
{
	siz[x]=1;f[0][x]=0;f[1][x]=-(1<<30);p[x]=x;
	int mx=0;Ans[1]+=dep;
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs1(v,x,dep+1);mx=max(mx,siz[v]);
		if(siz[v]==mx) mxp[x]=v;
		siz[x]+=siz[v];
		if(f[0][v]+1>f[0][x]) f[1][x]=f[0][x],p[x]=v,f[0][x]=f[0][v]+1;
		else if(f[0][v]+1>f[1][x]) f[1][x]=f[0][v]+1;
	}
	if(max(mx,n-siz[x])<=(n>>1))
	{
		if(n-siz[x]==(n>>1)) ok[x]=3;
		else if(mx==(n>>1)) ok[x]=2;
		else ok[x]=1;
	}
}

void dfs2(int x,int fa)
{
	if(fa)
	{
		g[x]=max(g[fa],(p[fa]==x?f[1][fa]:f[0][fa]))+1;
		Ans[x]=Ans[fa]+n-2*siz[x];
	}
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		dfs2(v,x);
	}
}

int main()
{
	read(n);
	for(int i=1,u,v;i<n;i++)
	{
		read(u);read(v);
		add(u,v);add(v,u);
	}
	dfs1(1,0,0);dfs2(1,0);
	for(int i=1;i<=n;i++)
		if(ok[i]==1) printf("%lld\n",2*Ans[i]-max(f[0][i],g[i]));
		else if(ok[i]==2) printf("%lld\n",2*Ans[i]-f[0][mxp[i]]-1);
		else if(ok[i]==3) printf("%lld\n",2*Ans[i]-g[i]);
		else puts("-1");
}