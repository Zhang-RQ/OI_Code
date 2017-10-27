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
#define MAXM 20100
#define MAXN 20010
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
int head[MAXM];
struct Node{
    int val,nxt,v;
}Edge[MAXN];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
struct a{
    int u,v,val;
    bool operator <(a a)
    {
        return val>a.val;
    }
}e[51000],e1[11000];
int f[10010],n,m,t1,t2,t3;
int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}
int cnt=0,k,cntt=0;
int pos[11000],siz[11000],son[11000],dep[11000],top[11000],fa[11000];
void dfs_1(int x,int father)
{
    siz[x]=1;fa[x]=father;
    dep[x]=dep[fa[x]]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x])  continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v]) son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    top[x]=tp;
    pos[x]=++cnt;
    if(son[x]) dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs_2(v,v);
    }
}
int tree[44000];
void insert(int x,int l,int r,int pos,int val)
{
    if(l==r) {tree[x]=val;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) insert(Ls,pos,val);
    else insert(Rs,pos,val);
    tree[x]=min(tree[x<<1],tree[x<<1|1]);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return tree[x];
    int mid=(l+r)>>1;
    int ret=0x3f3f3f3f;
    if(ql<=mid) ret=min(ret,query(Ls,ql,qr));
    if(qr>mid) ret=min(ret,query(Rs,ql,qr));
    return ret;
}
int solve(int x,int y)
{
    int ret=0x3f3f3f3f;
    while(top[x]!=top[y])
    {
        //printf("%d %d\n",x,y);
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ret=min(ret,query(1,1,cnt,pos[top[x]],pos[x]));
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    ret=min(ret,query(1,1,cnt,pos[y]+1,pos[x]));
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   f[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        e[i]={t1,t2,t3};
    }
    sort(e+1,e+1+m);
    for(int i=1;i<=m;i++)
    {
        int u=e[i].u,v=e[i].v;
        if(find(u)!=find(v))
        {
            add(u,v,e[i].val);
            add(v,u,e[i].val);
            f[find(u)]=find(v);
            e1[++cntt]=e[i];
        }
    }
    for(int i=1;i<=n;i++)
        if(!pos[i])
            dfs_1(i,0),
            dfs_2(i,i);
    for(int i=1;i<=cntt;i++)
    {
        int u_=e1[i].u,v_=e1[i].v;
        if(dep[u_]>dep[v_])
            swap(u_,v_);
        insert(1,1,cnt,pos[v_],e1[i].val);
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&t1,&t2);
        if(find(t1)==find(t2))
            printf("%d\n",solve(t1,t2));
        else puts("-1");
    }
}
