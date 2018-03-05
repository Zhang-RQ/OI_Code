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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int siz[MAXN],rt,mx_rt,t[MAXN<<1],mxdep;
bool vis[MAXN];
ll ans=0,f[MAXN<<1][2],g[MAXN<<1][2];
void get_root(int x,int fa,int sz)
{
    int mx=0;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        get_root(v,x,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void dfs(int x,int fa,int dis,int dep)
{
    mxdep=max(dep,mxdep);
    if(t[dis]) g[dis][1]++;
    else g[dis][0]++;
    t[dis]++;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        dfs(v,x,dis+Edge[i].w,dep+1);
    }
    t[dis]--;
}
void solve(int x)
{
    vis[x]=1;f[MAXN][0]=1;
    int mx=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mxdep=1;
        dfs(v,0,MAXN+Edge[i].w,1);
        ans+=g[MAXN][0]*(f[MAXN][0]-1);mx=max(mxdep,mx);
        for(int j=-mxdep;j<=mxdep;j++)
            ans+=g[MAXN+j][0]*f[MAXN-j][1]+g[MAXN+j][1]*f[MAXN-j][0]+g[MAXN+j][1]*f[MAXN-j][1];
        for(int j=MAXN-mxdep;j<=MAXN+mxdep;j++)
        {
            f[j][0]+=g[j][0];
            f[j][1]+=g[j][1];
            g[j][0]=g[j][1]=0;
        }
    }
    for(int j=MAXN-mx;j<=MAXN+mx;j++)
        f[j][0]=f[j][1]=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,siz[v]);
        solve(rt);
    }
}
int n,u,v,w;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)  scanf("%d%d%d",&u,&v,&w),w=w?1:-1,add(u,v,w),add(v,u,w);
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    cout<<ans<<endl;
}
