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
const int MAXN=10010;
const int MAXM=MAXN<<1;
struct node{
    int nxt,v,w;
}Edge[MAXM];
set<ll> s;
int head[MAXN],cnt_e;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int siz[MAXN],mx_rt,rt,ans[110],p,n;
ll Q[110];
bool vis[MAXN];
void get_root(int x,int fa,int sz)
{
    int mx=1;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        get_root(v,x,sz);
        mx=max(mx,siz[v]);
        siz[x]+=siz[v];
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void dfs(int x,int fa,ll dis)
{
    s.insert(dis);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs(Edge[i].v,x,dis+Edge[i].w);
}
void dfs2(int x,int fa,ll dis)
{
    for(int i=1;i<=p;i++) if(!ans[i])
        ans[i]|=(s.find(Q[i]-dis)!=s.end());
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs2(Edge[i].v,x,dis+Edge[i].w);
}
void solve(int x)
{
    s.clear();s.insert(0);vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        dfs2(v,0,Edge[i].w);
        dfs(v,0,Edge[i].w);
    }
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,siz[v]);
        solve(rt);
    }
}
int u,v,w;
int main()
{
    scanf("%d%d",&n,&p);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    for(int i=1;i<=p;i++) scanf("%lld",&Q[i]),ans[i]=Q[i]==0?1:0;
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    for(int i=1;i<=p;i++)
        puts(ans[i]?"Yes":"No");
}
