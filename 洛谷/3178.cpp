#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
typedef long long ll;
typedef unsigned long long ull;
#define MAXM 100010
#define MAXN 100010
#define int long long
int head[MAXM],val[MAXM];
struct Node{
    int v,nxt;
}Edge[MAXN<<1];
int cnte=0;
inline void add(int u,int v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
int top[MAXM],fa[MAXM],dep[MAXM],dfn[MAXM],son[MAXM],siz[MAXM];
ll arr[MAXM];
int cnt=0;
int N,M,root,u,v,w,x,y,z,ops;
void dfs_1(int x,int father)
{
    fa[x]=father;
    siz[x]=1;
    dep[x]=dep[father]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v]) son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    dfn[x]=++cnt;
    arr[cnt]=val[x];
    top[x]=tp;
    if(son[x])
        dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs_2(v,v);
    }
}
struct node{
    ll val,tag;
}tree[MAXM<<2];
void build(int x,int l,int r)
{
    if(l==r) {tree[x].val=arr[l];return;}
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
    return;
}
void pushdown(int x,int l,int r)
{
    if(tree[x].tag)
    {
        int mid=(l+r)>>1;
        tree[x<<1].val+=tree[x].tag*(mid-l+1);
        tree[x<<1|1].val+=tree[x].tag*(r-mid);
        tree[x<<1].tag+=tree[x].tag;
        tree[x<<1|1].tag+=tree[x].tag;
        tree[x].tag=0;
    }
}
void section_plus(int x,int l,int r,int cl,int cr,int val)
{
    if(cl>r||cr<l) return;
    if(cl<=l&&r<=cr) {tree[x].val+=val*(r-l+1);tree[x].tag+=val;return;}
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(cl<=mid)  section_plus(Ls,cl,cr,val);
    if(cr>mid)   section_plus(Rs,cl,cr,val);
    (tree[x].val=tree[x<<1].val+tree[x<<1|1].val);
    return;
}
ll query(int x,int l,int r ,int ql,int qr)
{
    if(ql>r||qr<l) return 0;
    if(ql<=l&&r<=qr) return tree[x].val;
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    ll ret=0;
    if(ql<=mid)  ret+=query(Ls,ql,qr);
    if(qr>mid)   ret+=query(Rs,ql,qr);
    return ret;
}
void path_plus(int x,int y,int val)
{
    int tx=top[x],ty=top[y];
    while(tx!=ty)
    {
        if(dep[tx]<dep[ty]) swap(x,y),swap(tx,ty);
        section_plus(1,1,cnt,dfn[tx],dfn[x],val);
        x=fa[tx];
        tx=top[x];
    }
    if(dep[x]<dep[y]) swap(x,y),swap(tx,ty);
    section_plus(1,1,cnt,dfn[y],dfn[x],val);
    return;
}
ll path_sum(int x,int y)
{
    ll ret=0;
    int tx=top[x],ty=top[y];
    while(tx!=ty)
    {
        if(dep[tx]<dep[ty]) swap(x,y),swap(tx,ty);
        (ret+=query(1,1,cnt,dfn[tx],dfn[x]));
        x=fa[tx];
        tx=top[x];
    }
    if(dep[x]<dep[y]) swap(x,y),swap(tx,ty);
    (ret+=query(1,1,cnt,dfn[y],dfn[x]));
    return ret;
}
signed main()
{
    root=1;
    scanf("%lld%lld",&N,&M);
    for(int i=1;i<=N;i++) scanf("%lld",&val[i]);
    for(int i=1;i<N;i++)
    {
        scanf("%lld%lld",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs_1(root,0);
    dfs_2(root,root);
    build(1,1,cnt);
    for(int i=1;i<=M;i++)
    {

        scanf("%lld",&ops);
        if(ops==1)
        {
            scanf("%lld%lld",&x,&y);
            section_plus(1,1,cnt,dfn[x],dfn[x],y);
        }
        else if(ops==2)
        {
            scanf("%lld%lld",&x,&y);
            section_plus(1,1,cnt,dfn[x],dfn[x]+siz[x]-1,y);
        }
        else if(ops==3)
        {
            scanf("%lld",&x);
            printf("%lld\n",path_sum(1,x));
        }
    }
    return 0;
}
