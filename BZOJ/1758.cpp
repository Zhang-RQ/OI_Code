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

const int MAXN=1E5+10;
const int INF=1<<30;

namespace FastIO{
    inline char get_char()
    {
        return getchar();
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

bool vis[MAXN],srt[MAXN],fl;
double Mid,d[MAXN],d1[MAXN];
int n,siz[MAXN],rt,mx_rt,L,R,dep[MAXN],q[MAXN],MxDep,RRt;
vector<int> Rt[MAXN];
vector<pair<int,int> > g[MAXN];

void get_rt(int x,int fa,int sz)
{
    int mx=0;siz[x]=1;
    for(auto v:g[x])
        if(v.first!=fa&&!vis[v.first])
            get_rt(v.first,x,sz),siz[x]+=siz[v.first],mx=max(mx,siz[v.first]);
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}

void get_dep(int x,int fa)
{
    dep[x]=1;
    for(auto v:g[x])
        if(v.first!=fa&&!vis[v.first])
            get_dep(v.first,x),
            dep[x]=max(dep[x],dep[v.first]+1);
}

void dfs(int x,int fa,int dep,double val)
{
    d1[dep]=max(d1[dep],val);MxDep=max(MxDep,dep);
    for(auto v:g[x])
        if(v.first!=fa&&!vis[v.first])
            dfs(v.first,x,dep+1,val+v.second-Mid);
}

void solve(int x)
{
    if(fl) return;
    vis[x]=1;
    if(!srt[x])
    {
        get_dep(x,0);
        sort(g[x].begin(),g[x].end(),[](const pair<int,int> &lhs,const pair<int,int> &rhs)->bool{return dep[lhs.first]<dep[rhs.first];});
        srt[x]=1;
    }
    d[0]=0;
    int mx=MxDep=0;
    for(auto v:g[x])
    {
        if(vis[v.first]) continue;
        if(fl) break;
        dfs(v.first,x,1,v.second-Mid);
        int head=1,tail=0;
        for(int i=min(R-1,mx);i>=L;i--)
        {
            while(head<=tail&&d[q[tail]]<=d[i]) --tail;
            q[++tail]=i;
        }
        for(int i=1;i<=MxDep;i++)
        {
            if(L-i>=0)
            {
                while(head<=tail&&d[q[tail]]<=d[L-i]) --tail;
                q[++tail]=L-i;
            }
            while(head<=tail&&q[head]+i>R) ++head;
            if(d1[i]+d[q[head]]>=0) fl=1;
        }
        mx=MxDep;
        for(int j=1;j<=mx;j++)
            d[j]=max(d[j],d1[j]);
        for(int j=1;j<=mx;j++)
            d1[j]=-INF;
    }
    for(int j=0;j<=mx;j++)
        d[j]=-INF;
    for(int v:Rt[x])
        solve(v);
    if(fl) return;

}

void build(int x)
{
    vis[x]=1;
    for(auto v:g[x])
        if(!vis[v.first])
        {
            mx_rt=1<<30;
            get_rt(v.first,x,siz[v.first]);
            Rt[x].push_back(rt);
            build(rt);
        }
}

void init()
{
    mx_rt=1<<30;get_rt(1,0,n);
    RRt=rt;
    build(rt);
}

bool check(double x)
{
    Mid=x;memset(vis,0,sizeof vis);fl=0;
    solve(RRt);
    return fl;
}

int main()
{
    read(n,L,R);
    for(int i=0;i<=n;i++)
        d[i]=d1[i]=-INF;
    for(int i=1,u,v,w;i<n;i++)
        read(u,v,w),g[u].push_back({v,w}),g[v].push_back({u,w});
    init();
    double L=0,R=1000000;
    for(int i=1;i<=35;i++)
    {
        double mid=(L+R)/2;
        bool f=check(mid);
        if(f) L=mid;
        else R=mid;
    }
    printf("%.3lf\n",L);
}