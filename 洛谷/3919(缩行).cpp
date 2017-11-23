#include<cstdio>
#define MAXN 1000010
#define mid ((l+r)>>1)
#define Ls t[x].l,l,mid
#define Rs t[x].r,mid+1,r
using namespace std;
struct node{
    int v,l,r;
}t[MAXN*20];
int rt[MAXN],arr[MAXN],cnt,n,m,opt,v,loc,val;
void build(int &x,int l,int r)
{
    !x?x=++cnt:0;
    if(l==r) {t[x].v=arr[l];return;}
    build(Ls);build(Rs);
}
void change(int &x,int l,int r,int y,int vl,int ps)
{
    !x?x=++cnt:0;
    if(l==r) {t[x].v=vl;return;}
    t[x]=t[y];ps<=mid?change(t[x].l=0,l,mid,t[y].l,vl,ps):change(t[x].r=0,mid+1,r,t[y].r,vl,ps);
}
int query(int x,int l,int r,int ps)  {return l==r?t[x].v:(ps<=mid?query(Ls,ps):query(Rs,ps));}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
    build(rt[0],1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&v,&opt,&loc);
        if(opt==1) scanf("%d",&val),change(rt[i],1,n,rt[v],val,loc);
        else printf("%d\n",query(rt[v],1,n,loc)),t[rt[i]=++cnt]=t[rt[v]];
    }
}
