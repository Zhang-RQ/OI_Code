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
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int c[MAXN],cnt[MAXN],has[MAXN],siz[MAXN],sz[MAXN],rt,mx_rt,stk[MAXN],top,ct[MAXN],ccnt[MAXN],path,tstk[MAXN];
ll tot,sum[MAXN];
bool vis[MAXN],exist[MAXN];
void get_root(int x,int fa,int siiz)
{
    int mx=1;sz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        get_root(v,x,siiz);
        sz[x]+=sz[v];
        mx=max(mx,sz[v]);
    }
    mx=max(mx,siiz-sz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void get_siz(int x,int fa)
{
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        get_siz(v,x);
        siz[x]+=siz[v];
    }
}
void dfs(int x,int fa,int *_cnt)
{
    if(!exist[c[x]]) stk[++top]=c[x],exist[c[x]]=1;
    if(++has[c[x]]==1) _cnt[c[x]]+=siz[x];
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs(Edge[i].v,x,_cnt);
    --has[c[x]];
}
void update(int x,int fa,ll lst)
{
    if(++has[c[x]]==1) lst+=path-cnt[c[x]];
    sum[x]+=lst+tot;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            update(Edge[i].v,x,lst);
    --has[c[x]];
}
void calc(int x)
{
    get_siz(x,0);
    top=0;dfs(x,0,cnt);tot=0;
    int ttop=top;
    for(int i=1;i<=top;i++)
        tot+=cnt[tstk[i]=stk[i]],
        ccnt[stk[i]]=cnt[stk[i]],
        exist[stk[i]]=0;
    sum[x]+=tot;
    ll tmp=tot;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        top=0;has[c[x]]=1;dfs(v,0,ct);has[c[x]]=0;
        cnt[c[x]]-=siz[v];tot-=siz[v];
        for(int j=1;j<=top;j++)
            tot-=ct[stk[j]],cnt[stk[j]]-=ct[stk[j]],exist[stk[j]]=0;
        path=siz[x]-siz[v];
        update(v,0,0);
        cnt[c[x]]+=siz[v];
        for(int j=1;j<=top;j++)
            cnt[stk[j]]=ccnt[stk[j]],ct[stk[j]]=0;
        tot=tmp;
    }
    for(int i=1;i<=ttop;i++)
        cnt[tstk[i]]=0;
}
void solve(int x)
{
    vis[x]=1;
    calc(x);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        mx_rt=MAXN+10;
        get_root(v,0,sz[v]);
        solve(rt);
    }
}
int n,u,v;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    for(int i=1;i<=n;i++)
        printf("%lld\n",sum[i]);
}
