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

const int MAXN=3E6+10;

int n,siz[MAXN],jmp[MAXN],d[MAXN],rt;
vector<pair<int,int> > g[MAXN];
vector<int> lf;
ll tAns,dlt[MAXN],f[MAXN],Sum,dep[MAXN];

void dfs(int x,int fa)
{
	if(fa) siz[x]=g[x].size()==1;
	for(auto e:g[x])
		if(e.first!=fa)
		{
			dep[e.first]=dep[x]+e.second;
			dfs(e.first,x);
			tAns+=(1+(~siz[e.first]&1))*e.second;
			siz[x]+=siz[e.first];
		}
	if(fa&&g[x].size()==1) lf.push_back(x);
}

void dfs1(int x,int fa)
{
	if(siz[x]>1) jmp[x]=x;
	else jmp[x]=jmp[fa];
	for(auto e:g[x])
		if(e.first!=fa)
		{
			dlt[e.first]=dlt[x]+e.second*(siz[e.first]&1?1:-1);
			f[e.first]=f[x]+e.second*(1+(~siz[e.first]&1));
			dfs1(e.first,x);
		}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),g[u].push_back({v,w}),g[v].push_back({u,w}),Sum+=w,d[u]++,d[v]++;
	for(int i=1;i<=n;i++)
		if(d[i]>1) {rt=i;break;}
	if(rt)
	{
		ll Ans=1ll<<60;
		dfs(rt,0);dfs1(rt,0);
		if(lf.size()&1)
			for(int x:lf)
				Ans=min(Ans,tAns+dlt[jmp[x]]+dep[x]-dep[jmp[x]]-(f[x]-f[jmp[x]]));
		else Ans=tAns;
		printf("%d %lld\n",(lf.size()+1)>>1,Ans);	
	}
	else printf("%d %lld\n",1,Sum);
}