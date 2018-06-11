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
const int MAXN=2E5+5;
const int MAXM=2E5+5;
struct __edge{
    int nxt,v;
    ll w;
}Edge[MAXM];
int head[MAXN],cnt_e,siz[MAXN],rt,rt_mx,stk[MAXN],top;
int pnt[MAXN],tot,fa[MAXN],n;
ll p[MAXN],q[MAXN],l[MAXN],dis[MAXN],f[MAXN];
double slp[MAXN];
inline double slope(int x,int y){return (1.0*f[y]-f[x])/(1.0*dis[y]-dis[x]);}
bool vis[MAXN];
void insert(int x)
{
    while(top>1&&slp[top-1]<=slope(stk[top-1],x)) top--;
    stk[++top]=x;slp[top-1]=slope(stk[top-1],x);slp[top]=-1E18;
}
int query(double S)
{
    int L=1,R=top,ret=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(slp[mid]<=S) ret=mid,R=mid-1;
        else L=mid+1;
    }
    return stk[ret];
}
inline void add(int u,int v,ll w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
void pre_dfs(int x)
{
    for(int i=head[x];i;i=Edge[i].nxt)
        dis[Edge[i].v]=dis[x]+Edge[i].w,
        pre_dfs(Edge[i].v);
}
void get_rt(int x,int sz)
{
    int mx=0;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        get_rt(v,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<=rt_mx) rt_mx=mx,rt=x; 
}
void dfs(int x)
{
    pnt[++tot]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]) dfs(Edge[i].v);
}
void solve(int x,int sz) // x is root
{
    if(sz==1) return;
    rt_mx=1<<30;get_rt(x,sz);
    int H=rt;
    for(int i=head[H];i;i=Edge[i].nxt)
        vis[Edge[i].v]=1,sz-=siz[Edge[i].v];
    solve(x,sz);
    tot=0;
    for(int i=head[H];i;i=Edge[i].nxt)
        dfs(Edge[i].v);
    sort(pnt+1,pnt+1+tot,[](int x,int y)->bool{return dis[x]-l[x]>dis[y]-l[y];});
    top=0;int tt=H;
    for(int i=1;i<=tot;i++)
    {
        int y=pnt[i];
        while(tt!=fa[x]&&dis[tt]>=dis[y]-l[y]) insert(tt),tt=fa[tt];
        if(top)
        {
            int k=query(p[y]);
            f[y]=min(f[y],f[k]+(dis[y]-dis[k])*p[y]+q[y]);
        }
    }
    for(int i=head[H];i;i=Edge[i].nxt)
        solve(Edge[i].v,siz[Edge[i].v]);
}
int main()
{
    scanf("%d%*d",&n);
    ll w;
    for(int i=2;i<=n;i++)
    {
        scanf("%d%lld%lld%lld%lld",&fa[i],&w,&p[i],&q[i],&l[i]);
        add(fa[i],i,w);f[i]=1ll<<60;
    }
    pre_dfs(1);
    solve(1,n);
    for(int i=2;i<=n;i++) printf("%lld\n",f[i]);
    #ifdef LOCAL
        system("pause");
    #endif
}