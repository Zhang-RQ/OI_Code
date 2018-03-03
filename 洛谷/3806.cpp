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
const int MAXK=10000000;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e;
int cnt[MAXK+1],siz[MAXN],vis[MAXN],rt=0,mx_rt=0,p,dis[MAXN],stk[MAXN];
int n,m,u,v,w;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
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
void get_dis(int x,int fa)
{
    stk[++p]=dis[x];
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[x]+Edge[i].w;
        get_dis(v,x);
    }
}
void calc(int x,int val,bool flag)
{
    p=0;
    dis[x]=val;get_dis(x,0);
    for(int i=1;i<=p;i++)
        for(int j=1;j<=p;j++)
            if(stk[i]+stk[j]<=MAXK&&flag)
                ++cnt[stk[i]+stk[j]];
            else --cnt[stk[i]+stk[j]];
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
        mx_rt=MAXK;
        get_root(v,0);
        solve(rt);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
        scanf("%d%d%d",&u,&v,&w),
        add(u,v,w),add(v,u,w);
    mx_rt=MAXK;
    get_root(1,0);
    solve(rt);
    while(m--)
    {
        scanf("%d",&w);
        if(cnt[w]) puts("AYE");
        else puts("NAY");
    }
    return 0;
}
