#include<cstdio>
using namespace std;
struct node{
    int val,ls,rs;
}tree[1000010*20];
int rt[1001000],arr[1001000];
int cnt=0,n,m;
void build(int &x,int l,int r)
{
    if(!x)
        x=++cnt;
    if(l==r)
        {tree[x].val=arr[l];return;}
    int mid=(l+r)>>1;
    build(tree[x].ls,l,mid);
    build(tree[x].rs,mid+1,r);
}
void change(int &x,int l,int r,int x_,int val,int pos)
{
    if(!x)
        x=++cnt;
    if(l==r)
        {tree[x].val=val;return;}
    tree[x]=tree[x_];
    int mid=(l+r)>>1;
    if(pos<=mid)
        change(tree[x].ls=0,l,mid,tree[x_].ls,val,pos);
    else
        change(tree[x].rs=0,mid+1,r,tree[x_].rs,val,pos);
}
int query(int x,int l,int r,int pos)
{
    if(l==r)
        return tree[x].val;
    int mid=(l+r)>>1;
    if(pos<=mid)
        return query(tree[x].ls,l,mid,pos);
    else
        return query(tree[x].rs,mid+1,r,pos);
}
int opt,v,loc,val;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    build(rt[0],1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&v,&opt,&loc);
        if(opt==1)
            scanf("%d",&val),
            change(rt[i],1,n,rt[v],val,loc);
        else
            printf("%d\n",query(rt[v],1,n,loc)),
            tree[rt[i]=++cnt]=tree[rt[v]];
    }
}
