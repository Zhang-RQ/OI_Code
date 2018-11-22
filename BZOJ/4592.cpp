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

const int MAXN=2E5+10;

struct dat{
    int l,r,c,a,ln,s;
    dat(int _l=0,int _r=0,int _c=0,int _a=0,int _ln=0,int _s=0) {l=_l;r=_r;c=_c;a=_a;ln=_ln;s=_s;}

    void All_0(int len)
    {
        l=r=c=len;a=1;
        ln=len;s=0;
    }

    void All_1(int len)
    {
        l=r=c=0;a=0;
        ln=s=len;
    }

    friend dat operator + (const dat &lhs,const dat &rhs)
    {
        dat ret;
        ret.l=lhs.a?(lhs.ln+rhs.l):(lhs.l);
        ret.r=rhs.a?(rhs.ln+lhs.r):(rhs.r);
        ret.c=max(max(lhs.c,rhs.c),lhs.r+rhs.l);
        ret.a=lhs.a&&rhs.a;
        ret.ln=lhs.ln+rhs.ln;
        ret.s=lhs.s+rhs.s;
        return ret;
    }
}t[MAXN<<3];

int tg[MAXN<<3],n,m;

void pushup(int x){t[x]=t[x<<1]+t[x<<1|1];}

void pushdown(int x)
{
    if(tg[x]==0)
    {
        t[x<<1].All_0(t[x<<1].ln);
        t[x<<1|1].All_0(t[x<<1|1].ln);
        tg[x<<1]=tg[x<<1|1]=0;
        tg[x]=-1;
    }
    if(tg[x]==1)
    {
        t[x<<1].All_1(t[x<<1].ln);
        t[x<<1|1].All_1(t[x<<1|1].ln);
        tg[x<<1]=tg[x<<1|1]=1;
        tg[x]=-1;
    }
}

void build(int x,int l,int r)
{
    if(l==r) return t[x].All_1(1),void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}

void change(int x,int l,int r,int cl,int cr,int v)
{
    if(cl>cr) return;
    if(cl<=l&&r<=cr) return tg[x]=v,v?t[x].All_1(r-l+1):t[x].All_0(r-l+1);
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,v);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,v);
    pushup(x);
}

dat query(int x,int l,int r,int ql,int qr)
{
    if(ql>qr) return dat();
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;pushdown(x);
    if(qr<=mid) return query(x<<1,l,mid,ql,qr);
    else if(ql>mid) return query(x<<1|1,mid+1,r,ql,qr);
    else return query(x<<1,l,mid,ql,qr)+query(x<<1|1,mid+1,r,ql,qr);
}

int query_s(int x,int l,int r,int ql,int qr)
{
    if(ql>qr) return 0;
    if(ql<=l&&r<=qr) return t[x].s;
    int mid=(l+r)>>1;pushdown(x);
    if(qr<=mid) return query_s(x<<1,l,mid,ql,qr);
    else if(ql>mid) return query_s(x<<1|1,mid+1,r,ql,qr);
    else return query_s(x<<1,l,mid,ql,qr)+query_s(x<<1|1,mid+1,r,ql,qr);
}

int main()
{
    memset(tg,-1,sizeof tg);
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1,c,l,r,l1,r1;i<=m;i++)
    {
        scanf("%d",&c);
        if(c==0) scanf("%d%d",&l,&r),change(1,1,n,l,r,0);
        else if(c==1)
        {
            scanf("%d%d%d%d",&l,&r,&l1,&r1);
            int s=query_s(1,1,n,l,r);
            change(1,1,n,l,r,0);
            int L=l1,R=r1,Ans=0;
            while(L<=R)
            {
                int mid=(L+R)>>1;
                if(query_s(1,1,n,l1,mid)+s>=mid-l1+1) Ans=mid,L=mid+1;
                else R=mid-1;
            }
            change(1,1,n,l1,Ans,1);
        }
        else scanf("%d%d",&l,&r),printf("%d\n",query(1,1,n,l,r).c);
    }
}