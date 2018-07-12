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

const int MAXN=1E5+5;
const ll IINF=0xcfcfcfcfcfcfcfcf;

vector<int> g[MAXN];
int cnt_e,rt,mx_rt,n;
int val[MAXN],siz[MAXN],L,R;
bool cls[MAXN<<2],vis[MAXN];
ll ans[MAXN],tag[MAXN],t[MAXN<<2];

inline void pushdown(const int &x) {if(cls[x]) t[x<<1]=t[x<<1|1]=IINF,cls[x<<1]=cls[x<<1|1]=1,cls[x]=0;}

inline void clear() {cls[1]=1;t[1]=IINF;}

void change(int x,int l,int r,int pos,ll val)
{
    if(l==r) return t[x]=max(t[x],val),void();
    int mid=(l+r)>>1;pushdown(x);
    if(pos<=mid) change(x<<1,l,mid,pos,val);
    else change(x<<1|1,mid+1,r,pos,val);
    t[x]=max(t[x<<1],t[x<<1|1]);
}

ll query(int x,int l,int r,int ql,int qr)
{
    if(t[x]==IINF) return IINF;
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;ll ret=IINF;pushdown(x);
    if(ql<=mid) ret=max(ret,query(x<<1,l,mid,ql,qr));
    if(qr>mid) ret=max(ret,query(x<<1|1,mid+1,r,ql,qr));
    return ret;
}

void get_rt(int x,int fa,int sz)
{
    int mx=siz[x]=1;
    for(auto v:g[x])
    {
        if(v==fa||vis[v]) continue;
        get_rt(v,x,sz);
        siz[x]+=siz[v];
        mx=max(mx,siz[v]);
    }
    mx=max(mx,sz-siz[x]);
    if(mx<mx_rt) rt=x,mx_rt=mx;
}

void dfs_c(int x,int fa,ll sum,int dep)
{
    if(dep>R) return;
    change(1,0,R,dep,sum+val[x]);
    for(auto v:g[x])
    {
        if(v==fa||vis[v]) continue;
        dfs_c(v,x,sum+val[x],dep+1);
    }
}

void dfs_q(int x,int fa,ll sum,int dep)
{
    if(dep>R) return;
    tag[x]=max(tag[x],query(1,0,R,max(L-dep,0),R-dep)+sum+val[x]);
    for(auto v:g[x])
    {
        if(v==fa||vis[v]) continue;
        dfs_q(v,x,sum+val[x],dep+1);
    }
}

void pushtag(int x,int fa)
{
    for(auto v:g[x])
    {
        if(v==fa||vis[v]) continue;
        pushtag(v,x);
    }
    tag[fa]=max(tag[fa],tag[x]);
    ans[x]=max(ans[x],tag[x]);tag[x]=IINF;
}

void solve(int x)
{
    vis[x]=1;
    clear(),change(1,0,R,0,val[x]);
    for(auto v:g[x])
    {
        if(vis[v]) continue;
        dfs_q(v,x,0,1);
        dfs_c(v,x,val[x],1);
    }
    reverse(g[x].begin(),g[x].end());
    clear(),change(1,0,R,0,val[x]);
    for(auto v:g[x])
    {
        if(vis[v]) continue;
        dfs_q(v,x,0,1);
        dfs_c(v,x,val[x],1);
    }
    pushtag(x,0);
    for(auto v:g[x])
    {
        if(vis[v]) continue;
        mx_rt=MAXN;
        get_rt(v,x,siz[v]);
        solve(rt);
    }
}

int main()
{
    memset(ans,0xcf,sizeof ans);memset(tag,0xcf,sizeof tag);
    scanf("%d%d%d",&n,&L,&R);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    mx_rt=MAXN;
    get_rt(1,0,n);
    solve(rt);
    for(int i=1;i<=n;i++) printf("%lld%c",ans[i],i==n?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}