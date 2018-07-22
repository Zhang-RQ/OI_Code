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

const int MAXN=20010;

int n,m,lstans;
int a[MAXN],aa[MAXN],cnt,rt[MAXN],q[4];
vector<int> v[MAXN];


struct node{
    int l,r;
    int lmx,rmx,sum;
}t[MAXN<<8];

inline void pushup(const int &x)
{
    t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
    t[x].lmx=max(t[t[x].l].lmx,t[t[x].l].sum+t[t[x].r].lmx);
    t[x].rmx=max(t[t[x].r].rmx,t[t[x].r].sum+t[t[x].l].rmx);
}

void build(int &x,int l,int r)
{
    x=++cnt;
    if(l==r) return t[x].sum=1,t[x].lmx=t[x].rmx=1,void();
    int mid=(l+r)>>1;
    build(t[x].l,l,mid);build(t[x].r,mid+1,r);
    pushup(x);
}

void change(int &x,int l,int r,int pos,int val,int _x)
{
    x=++cnt;
    t[x]=t[_x];
    if(l==r) return t[x].sum=val,t[x].lmx=t[x].rmx=max(val,0),void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(t[x].l,l,mid,pos,val,t[_x].l);
    if(pos>mid)  change(t[x].r,mid+1,r,pos,val,t[_x].r);
    pushup(x);
}

int query_s(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x].sum;
    int mid=(l+r)>>1,ret=0;
    if(ql<=mid) ret+=query_s(t[x].l,l,mid,ql,qr);
    if(qr>mid)  ret+=query_s(t[x].r,mid+1,r,ql,qr);
    return ret;
}

pair<int,int> query_l(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return make_pair(t[x].lmx,t[x].sum);
    int mid=(l+r)>>1;
    if(qr<=mid) return query_l(t[x].l,l,mid,ql,qr);
    if(ql>mid)  return query_l(t[x].r,mid+1,r,ql,qr);
    else
    {
        pair<int,int> L=query_l(t[x].l,l,mid,ql,qr),R=query_l(t[x].r,mid+1,r,ql,qr);
        return make_pair(max(L.first,L.second+R.first),L.second+R.second);
    }
}

pair<int,int> query_r(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return make_pair(t[x].rmx,t[x].sum);
    int mid=(l+r)>>1;
    if(qr<=mid) return query_r(t[x].l,l,mid,ql,qr);
    if(ql>mid)  return query_r(t[x].r,mid+1,r,ql,qr);
    else
    {
        pair<int,int> L=query_r(t[x].l,l,mid,ql,qr),R=query_r(t[x].r,mid+1,r,ql,qr);
        return make_pair(max(R.first,R.second+L.first),L.second+R.second);
    }
}

inline bool chk(int x,const int &a,const int &b,const int &c,const int &d)
{
    int L=query_r(rt[x],1,n,a,b-1).first,X=query_s(rt[x],1,n,b,c),R=query_l(rt[x],1,n,c+1,d).first;
    return L+X+R>=0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),aa[i]=a[i];
    sort(aa+1,aa+1+n);
    int cnt=unique(aa+1,aa+1+n)-aa-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(aa+1,aa+cnt+1,a[i])-aa,v[a[i]].push_back(i);
    build(rt[1],1,n);
    for(int i=2;i<=cnt;i++)
    {
        int trt=rt[i-1];
        for(int j=0;j<v[i-1].size();j++)
            change(trt,1,n,v[i-1][j],-1,trt);
        rt[i]=trt;
    }
    scanf("%d",&m);
    for(int i=1,a,b,c,d,L,R,ans;i<=m;i++)
    {
        scanf("%d%d%d%d",&q[0],&q[1],&q[2],&q[3]);
        q[0]=(q[0]+lstans)%n+1;q[1]=(q[1]+lstans)%n+1;
        q[2]=(q[2]+lstans)%n+1;q[3]=(q[3]+lstans)%n+1;
        sort(q,q+4);
        a=q[0],b=q[1],c=q[2],d=q[3];
        L=1,R=cnt,ans=0;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(chk(mid,a,b,c,d)) L=mid+1,ans=mid;
            else R=mid-1;
        }
        printf("%d\n",lstans=aa[ans]);
    }
}