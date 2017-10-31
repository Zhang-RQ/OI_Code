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
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
#define MAXM 100010
int head[MAXM];
struct Node{
    int v,nxt;
}Edge[MAXN<<1];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
struct node{
    int val;int tag;
}tree[MAXN<<2];
int siz[MAXN],son[MAXN],dep[MAXN],top[MAXN],dfn[MAXN],fa[MAXN];
int cnt=0;
void dfs_1(int x,int father)
{
    fa[x]=father;
    siz[x]=1;dep[x]=dep[fa[x]]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v])
            son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    top[x]=tp;
    dfn[x]=++cnt;
    if(son[x])
        dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==son[x]||v==fa[x])
            continue;
        dfs_2(v,v);
    }
}
inline void pushup(int x)
{
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
}
inline void pushdown(int x,int l,int r)
{
    if(tree[x].tag)
    {
        int mid=(l+r)>>1;
        tree[x<<1].val=(tree[x].tag-1)*(mid-l+1);
        tree[x<<1|1].val=(tree[x].tag-1)*(r-mid);
        tree[x<<1].tag=tree[x<<1|1].tag=tree[x].tag;
        tree[x].tag=0;
    }
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr)
    {
        tree[x].tag=val+1;
        tree[x].val=(r-l+1)*val;
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid) change(x<<1|1,mid+1,r,cl,cr,val);
    pushup(x);
}
void install(int x)
{
    while(top[x]!=1)
    {
        change(1,1,cnt,dfn[top[x]],dfn[x],1);
        x=fa[top[x]];
    }
    change(1,1,cnt,dfn[top[x]],dfn[x],1);
}
int main()
{
    int n,m,t1;
    char ops[20];
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&t1);
        t1++;
        add(i,t1);add(t1,i);
    }
    dfs_1(1,0);
    dfs_2(1,1);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%s",ops+1);
        scanf("%d",&t1);
        t1++;
        int tmp=tree[1].val;
        if(ops[1]=='i')
            install(t1);
        if(ops[1]=='u')
            change(1,1,cnt,dfn[t1],dfn[t1]+siz[t1]-1,0);
        printf("%d\n",abs(tree[1].val-tmp));
    }
}
