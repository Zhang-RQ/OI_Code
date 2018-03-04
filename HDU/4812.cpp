#pragma comment(linker,"/STACK:102400000,102400000")
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
#define P 1000003
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
int inv[P],val[MAXN],siz[MAXN],mx_rt,rt,dis[MAXN],stk[MAXN],top,id[MAXN],mp[P];
bool vis[MAXN];
int L,R;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void init()
{
    inv[1]=1;
    for(int i=2;i<P;i++)
    {
        int a=P/i,b=P%i;
        inv[i]=(1ll*(-a)*inv[b]%P+P)%P;
    }
}
int k;
void get_root(int x,int fa,int sz)
{
    int mx=1;siz[x]=1;
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
    stk[++top]=dis[x];id[top]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]||v==fa) continue;
        dis[v]=(1ll*dis[x]*val[v])%P;
        dfs(v,x);
    }
}
void query(int val,int _id)
{
    int tmp=(1ll*k*inv[val])%P;
    if(!mp[tmp]) return;
    int __id=mp[tmp];
    if(_id>__id) swap(_id,__id);
    if(_id<L||(_id==L&&__id<R)) L=_id,R=__id;
}
void solve(int x)
{
    vis[x]=1;mp[val[x]]=x;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        dis[v]=val[v]%P;top=0;
        dfs(v,0);
        for(int j=1;j<=top;j++)  query(stk[j],id[j]);
        dis[v]=(1ll*val[v]*val[x])%P;top=0;
        dfs(v,0);
        for(int j=1;j<=top;j++) if(!mp[stk[j]]||mp[stk[j]]>id[j]) mp[stk[j]]=id[j];
    }
    mp[val[x]]=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        dis[v]=(1ll*val[v]*val[x])%P;top=0;
        dfs(v,0);
        for(int j=1;j<=top;j++) mp[stk[j]]=0;
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
int n,u,v;
int main()
{
    init();
    while(~scanf("%d%d",&n,&k))
    {
        memset(head,0,sizeof head);
        memset(vis,0,sizeof vis);
        cnt_e=0;
        for(int i=1;i<=n;i++) scanf("%d",&val[i]);
        for(int i=1;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
        mx_rt=MAXN+10;
        get_root(1,0,n);
        L=R=P;
        solve(rt);
        if(L!=P) printf("%d %d\n",L,R);
        else puts("No solution");
    }
}
