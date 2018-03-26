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
const int MAXN=100010;
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
int t[MAXN<<2],tag[MAXN<<2],dep[MAXN],siz[MAXN],n,m,u,v,pos[MAXN],tot;
char opt[10];
void update(int &x,int y) // y->x
{
    x=dep[x]>dep[y]?x:y;
}
void pushdown(int x)
{
    if(tag[x])
    {
        update(tag[x<<1],tag[x]);
        update(tag[x<<1|1],tag[x]);
        update(t[x<<1],tag[x]);
        update(t[x<<1|1],tag[x]);
        tag[x]=0;
    }
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {update(tag[x],val);update(t[x],val);return;}
    int mid=(l+r)>>1;
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
}
int query(int x,int l,int r,int pos)
{
    if(l==r) return t[x];
    int mid=(l+r)>>1;
    pushdown(x);
    if(pos<=mid) return query(x<<1,l,mid,pos);
    else return query(x<<1|1,mid+1,r,pos);
}
void dfs(int x,int fa)
{
    siz[x]=1;pos[x]=++tot;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfs(v,x);
        siz[x]+=siz[v];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dep[1]=1;
    dfs(1,0);
    change(1,1,n,1,n,1);
    for(int i=1;i<=m;i++)
    {
        scanf("%s%d",opt+1,&u);
        if(opt[1]=='Q') printf("%d\n",query(1,1,n,pos[u]));
        else if(opt[1]=='C') change(1,1,n,pos[u],pos[u]+siz[u]-1,u);
    }
}
