%:pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define Ls tree[x].ls,l,mid
#define Rs tree[x].rs,mid+1,r
const int MAXN=100010<<1;
const int MAXM=200010<<1;
const int MAXC=100010<<1;
int head[MAXN];
struct Node{
    int v,nxt;
}Edge[MAXM<<1];
int cnte=0;
inline void add(const int &u,const int &v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
int pos[MAXN],top[MAXN],fa[MAXN],siz[MAXN],son[MAXN],dep[MAXN],val[MAXN];
int cnt=1;
int tot=0;
void dfs_1(int x,int father)
{
    siz[x]=1;fa[x]=father;dep[x]=dep[father]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father)
            continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v])
            son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    pos[x]=++tot;
    top[x]=tp;
    if(son[x])
        dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x])
            continue;
        dfs_2(v,v);
    }
}
struct NODE{
    int val,ls,rs,mx;
}tree[5000100<<1];
int rt[MAXC],col[MAXN];
int n,q,x,y;
char opt[20];
void change(int x,int l,int r,int pos,int val)
{
    if(l==r)
        {tree[x].val=tree[x].mx=val;return;}
    int mid=(l+r)>>1;
    if(pos<=mid)
    {
        if(!tree[x].ls)  tree[x].ls=++cnt;
        change(Ls,pos,val);
    }
    else
    {
        if(!tree[x].rs)  tree[x].rs=++cnt;
        change(Rs,pos,val);
    }
    tree[x].val=tree[tree[x].ls].val+tree[tree[x].rs].val;
    tree[x].mx=max(tree[tree[x].ls].mx,tree[tree[x].rs].mx);
    //printf("%d,%d,%d,mx=%d,val=%d\n",x,l,r,tree[x].mx,tree[x].val);
}
int querymax(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)
        return tree[x].mx;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid&&tree[x].ls)
        ret=max(ret,querymax(Ls,ql,qr));
    if(qr>mid&&tree[x].rs)
        ret=max(ret,querymax(Rs,ql,qr));
    return ret;
}
int querysum(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)
        return tree[x].val;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid&&tree[x].ls)
        ret+=querysum(Ls,ql,qr);
    if(qr>mid&&tree[x].rs)
        ret+=querysum(Rs,ql,qr);
    return ret;
}
void insert(int c,int pos,int val_)
{
    if(!rt[c])
        rt[c]=++cnt;
    //printf("c=%d:\n",c);
    change(rt[c],1,n,pos,val_);
}
int query(int l,int r,int c,int opt)  //opt=1,max;opt=2,sum
{
    if(!rt[c])
        return 0;
    if(opt==1)
        return querymax(rt[c],1,n,l,r);
    return querysum(rt[c],1,n,l,r);
}
int asksum(int x,int y,int c)
{
    int ret=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ret+=query(pos[top[x]],pos[x],c,2);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    ret+=query(pos[y],pos[x],c,2);
    return ret;
}
int askmax(int x,int y,int c)
{
    int ret=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ret=max(ret,query(pos[top[x]],pos[x],c,1));
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    ret=max(ret,query(pos[y],pos[x],c,1));
    return ret;
}
void change_c(int pnt,int nw,int val)
{
    insert(col[pnt],pos[pnt],0);
    insert(nw,pos[pnt],val);
    col[pnt]=nw;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&val[i],&col[i]);
    for(int i=1;i<n;i++)
        scanf("%d%d",&x,&y),
        add(x,y),
        add(y,x);
    dfs_1(1,0);
    dfs_2(1,1);
    for(int i=1;i<=n;i++)
        insert(col[i],pos[i],val[i]);
    for(int i=1;i<=q;i++)
    {
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='C'&&opt[1]=='C')
            change_c(x,y,val[x]);
        if(opt[0]=='C'&&opt[1]=='W')
            insert(col[x],pos[x],val[x]=y);
        if(opt[0]=='Q'&&opt[1]=='M')
            printf("%d\n",askmax(x,y,col[x]));
        if(opt[0]=='Q'&&opt[1]=='S')
            printf("%d\n",asksum(x,y,col[x]));
    }
}
