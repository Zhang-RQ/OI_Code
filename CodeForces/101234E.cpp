#include<bits/stdc++.h>

using namespace std;

const int MAXN=2E5+10;
const int INF=1<<30;

int lans[MAXN<<3],mx[MAXN<<3],v[MAXN<<3],p[MAXN],c[MAXN],n,f[MAXN],Ans,lst;
int mn[MAXN];

int solve(int x,int l,int r,int k)
{
    int ret=0;
    int mid=(l+r)>>1;
    if(l==r) ret=(mx[x]>k||k==0)?v[x]:INF;
    else if(k<mx[x<<1|1]) ret=min(lans[x],solve(x<<1|1,mid+1,r,k));
    else ret=solve(x<<1,l,mid,k);
    return ret;
}

int query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) {int ret=solve(x,l,r,lst);lst=max(lst,mx[x]);return ret;}
    int mid=(l+r)>>1,ret=INF;
    if(qr>mid) ret=min(ret,query(x<<1|1,mid+1,r,ql,qr));
    if(ql<=mid)  ret=min(ret,query(x<<1,l,mid,ql,qr));
    return ret;
}

void change(int x,int l,int r,int pos,int val,int vval)
{
    if(l==r) return mx[x]=val,v[x]=vval,void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos,val,vval);
    else change(x<<1|1,mid+1,r,pos,val,vval);
    lans[x]=solve(x<<1,l,mid,mx[x<<1|1]);
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
}

int main()
{
    memset(lans,0x3f,sizeof lans);
    memset(v,0x3f,sizeof v);
    Ans=INF;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=n;i;i--) mn[i]=max(mn[i+1],p[i]);
    int ans=0;
    change(1,0,n,0,0,0);
    for(int i=1;i<=n;i++)
    {
        lst=0;
        f[i]=query(1,0,n,0,p[i])+c[i];
        change(1,0,n,p[i],i,f[i]);
    }
    for(int i=1;i<=n;i++) if(p[i]>mn[i+1]) Ans=min(Ans,f[i]);
    printf("%d\n",Ans);
}