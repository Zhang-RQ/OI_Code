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
const int MAXN=1E4+5;
const int MAXM=2E4+5;
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
int siz[MAXN],rt,mx_rt,stk[MAXN],n,k,top;
bool vis[MAXN];
ll ans;
void get_root(int x,int fa,int sz)
{
    int mx=1;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        get_root(v,x,sz);
        mx=max(siz[v],mx);
        siz[x]+=siz[v];
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) rt=x,mx_rt=mx;
}
void dfs(int x,int fa,int dep)
{
    stk[++top]=dep;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        dfs(v,x,dep+Edge[i].w);
    }
}
void calc(int x,int val,bool flag)
{
    top=0;
    dfs(x,0,val);
    sort(stk+1,stk+1+top);
    int l=1,r=top;
    ll tmp=0;
    while(l<r)
    {
        if(stk[l]+stk[r]<=k)
        {
            tmp+=r-l;  //stk[l] -> stk[l+1]...stk[r]
            l++;
        }
        else r--;
    }
    if(flag) ans+=tmp;
    else ans-=tmp;
}
void solve(int x)
{
    calc(x,0,1);
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(vis[v]) continue;
        calc(v,Edge[i].w,0);
        mx_rt=1000000;
        get_root(v,0,siz[v]);
        solve(rt);
    }
}
int u,v,w;
int main()
{
    while(scanf("%d%d",&n,&k)&&n&&k)
    {
        memset(head,0,sizeof head);
        memset(vis,0,sizeof vis);
        cnt_e=0;ans=0;
        for(int i=1;i<n;i++)
            scanf("%d%d%d",&u,&v,&w),
            add(u,v,w),add(v,u,w);
        mx_rt=1000000;
        get_root(1,0,n);
        solve(rt);
        printf("%lld\n",ans);
    }
    return 0;
}
