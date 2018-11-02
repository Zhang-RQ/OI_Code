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

const int MAXN=5E5+10;
const int MAXM=3E6+10;

struct dat{
	ll k,b;
	dat(ll _k=0,ll _b=0){k=_k;b=_b;}
	ll f(ll x) const {return k*x+b;}
	dat get(ll x){return dat(-k,x-b);}
	dat operator + (const dat &rhs) const {return dat(k+rhs.k,b+rhs.b);}
}f[MAXN],Sum;

double solve(const dat &a,const dat &b)
{
	if(a.k==b.k) return -1;
	return 1.0*(a.b-b.b)/(b.k-a.k);
}

struct __edge{
	int nxt,v,w;
}Edge[MAXM];

double L,R;
bool vis[MAXN],gg;
int head[MAXN],cnt_e,p[MAXN],n,m;
ll Ans1,Ans2,tot;

inline void add(int u,int v,int w)
{
	Edge[++cnt_e].v=v;
	Edge[cnt_e].nxt=head[u];
	Edge[cnt_e].w=w;
	head[u]=cnt_e;
}

void dfs(int x,int fa)
{
	if(gg) return;
	vis[x]=1;Sum=Sum+f[x];
	double l=solve(f[x],dat(0,0)),r=solve(f[x],dat(0,p[x]));
	if(l>r) swap(l,r);
	L=max(L,l);R=min(R,r);
	for(int i=head[x];i;i=Edge[i].nxt)
	{
		int v=Edge[i].v;
		if(v==fa) continue;
		if(vis[v])
		{
			if((f[x].k+f[v].k==0)&&(f[x].b+f[v].b!=Edge[i].w)) gg=1;
			else
			{
				double s=solve(f[x]+f[v],dat(0,Edge[i].w));
				if(s!=-1)
				{
					if(s<L||s>R) gg=1;
					else L=R=s;
				}
			}
		}
		else f[v]=f[x].get(Edge[i].w),dfs(v,x);
		if(gg) return;
	}
}

int main()
{
	read(n);read(m);
	for(int i=1;i<=n;i++) read(p[i]),tot+=p[i];
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);read(v);read(w);
		add(u,v,w);add(v,u,w);
	}
	for(int x=1;x<=n;x++)
		if(!vis[x])
		{
			L=-(1ll<<60);R=1ll<<60;gg=0;Sum=dat(0,0);
			f[x]=dat(1,0);dfs(x,0);L=ceil(L);R=floor(R);
			if(gg||L>R) return puts("NIE"),0;
			L=Sum.f(L);R=Sum.f(R);
			Ans1+=min(L,R);Ans2+=max(L,R);
		}
	printf("%lld %lld\n",tot-Ans2,tot-Ans1);
}