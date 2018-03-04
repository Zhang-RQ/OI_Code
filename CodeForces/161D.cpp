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
const int MAXN=5E4+5;
const int MAXM=1E5+5;
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
int n,k,siz[MAXN],stk[MAXN],top,mx_rt,rt,buk[501];
bool vis[MAXN];
ll ans=0;
void get_root(int x,int fa,int sz)
{
    int mx=siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        get_root(v,x,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx_rt>mx) mx_rt=mx,rt=x;
}
void dfs(int x,int fa,int dis)
{
    if(dis<=k) stk[++top]=dis;
    else return;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            dfs(Edge[i].v,x,dis+1);
}
void insert(int x,int fa,int dis)
{
    if(dis<=k) buk[dis]++;
    else return;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(!vis[Edge[i].v]&&Edge[i].v!=fa)
            insert(Edge[i].v,x,dis+1);
}

void solve(int x)
{
    vis[x]=1;
    memset(buk,0,sizeof buk);
    buk[0]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        top=0;dfs(v,0,1);
        for(int j=1;j<=top;j++) ans+=buk[k-stk[j]];
        insert(v,0,1);
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
int u,v;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    mx_rt=MAXN+10;
    get_root(1,0,n);
    solve(rt);
    cout<<ans<<endl;
}
