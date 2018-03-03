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
const int MAXN=2E4+5;
const int MAXM=5E4+5;
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
int vis[MAXN],siz[MAXN],rt,mx_rt;
int tot=0,ans=0,g[3];
int n,u,v,w;
void get_root(int x,int fa)
{
    int mx=1;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        get_root(v,x);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,n-siz[x]);
    if(mx<mx_rt) mx_rt=mx,rt=x;
}
void dfs(int x,int fa,int val)
{
    g[val]++;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        dfs(v,x,(val+Edge[i].w)%3);
    }
}
int calc(int x,int val)
{
    g[0]=g[1]=g[2]=0;
    dfs(x,0,val);
    return g[1]*g[2]*2+g[0]*g[0];
}
void solve(int x)
{
    ans+=calc(x,0);
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        ans-=calc(v,Edge[i].w%3);
        rt=0;mx_rt=MAXN+10000;
        get_root(v,0);
        solve(rt);
    }
}
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d%d%d",&u,&v,&w),w%=3,
        add(u,v,w),add(v,u,w);
    mx_rt=MAXN+10;
    get_root(1,0);
    solve(rt);
    int gc=gcd(ans,n*n);
    printf("%d/%d\n",ans/gc,n*n/gc);
    return 0;
}
