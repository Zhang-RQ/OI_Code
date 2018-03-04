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
const int MAXN=2E5+5;
const int MAXM=4E5+5;
const int INF=0x3f3f3f3f;
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
int siz[MAXN],dis[MAXN],t[1000010],mx_rt,rt,d[MAXN];
bool vis[MAXN];
int ans=INF,n,k;
void get_root(int x,int fa,int sz)
{
    int mx=1;
    siz[x]=1;
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
void dfs(int x,int fa)
{
    if(dis[x]<=k) ans=min(ans,t[k-dis[x]]+d[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[x]+Edge[i].w;
        d[v]=d[x]+1;
        dfs(v,x);
    }
}
void update(int x,int fa,bool flag)
{
    if(dis[x]<=k)
    {
        if(flag) t[dis[x]]=min(t[dis[x]],d[x]);
        else t[dis[x]]=INF;
    }
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        update(v,x,flag);
    }
}
void solve(int x)
{
    vis[x]=1;t[0]=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        dis[v]=Edge[i].w;d[v]=1;
        dfs(v,0);update(v,0,1);
    }
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]) update(Edge[i].v,0,0);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,siz[v]);
        solve(rt);
    }
}
int u,w,v;
int main()
{
    memset(t,0x3f,sizeof t);
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++)
        scanf("%d%d%d",&u,&v,&w),u++,v++,add(u,v,w),add(v,u,w);
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    if(ans!=INF) printf("%d\n",ans);
    else puts("-1");
    return 0;
}
