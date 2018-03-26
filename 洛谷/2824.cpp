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
struct opt{int l,r,w;}OP[MAXN];
int a[MAXN],n,m,qpos;
namespace SegmentTree{
    int t[MAXN<<3],tag[MAXN<<3];
    inline void pushdown(int x,int l,int r)
    {
        if(tag[x]!=-1)
        {
            if(l==r) {tag[x]=-1;return;}
            int mid=(l+r)>>1;
            tag[x<<1]=tag[x<<1|1]=tag[x];
            t[x<<1]=tag[x]*(mid-l+1);
            t[x<<1|1]=tag[x]*(r-mid);
            tag[x]=-1;
        }
    }
    inline void pushup(int x)
    {
        t[x]=t[x<<1]+t[x<<1|1];
    }
    void build(int x,int l,int r,int xx)
    {
        tag[x]=-1;t[x]=0;
        if(l==r) {t[x]=(a[l]>=xx);return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid,xx);build(x<<1|1,mid+1,r,xx);
        pushup(x);
    }
    void change(int x,int l,int r,int cl,int cr,int val)
    {
        if(cl<=l&&r<=cr) {tag[x]=val;t[x]=(r-l+1)*val;return;}
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
        if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
        pushup(x);
    }
    int query(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr) return t[x];
        pushdown(x,l,r);
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=query(x<<1,l,mid,ql,qr);
        if(qr>mid)  ret+=query(x<<1|1,mid+1,r,ql,qr);
        return ret;
    }
}
bool check(int x)
{
    SegmentTree::build(1,1,n,x);
    for(int i=1;i<=m;i++)
    {
        int tot=SegmentTree::query(1,1,n,OP[i].l,OP[i].r);
        if(tot==0) continue;
        SegmentTree::change(1,1,n,OP[i].l,OP[i].r,0);
        if(OP[i].w==0)  SegmentTree::change(1,1,n,OP[i].r-tot+1,OP[i].r,1);
        else SegmentTree::change(1,1,n,OP[i].l,OP[i].l+tot-1,1);
    }
    return SegmentTree::query(1,1,n,qpos,qpos)>0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&OP[i].w,&OP[i].l,&OP[i].r);
    scanf("%d",&qpos);
    int L=1,R=n,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) ans=mid,L=mid+1;
        else R=mid-1;
    }
    printf("%d\n",ans);
}
