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
#define MAXN 100100
using namespace std;
typedef long long ll;
struct node{
    int val,lazy;
}tree[MAXN<<2];
void build(int x,int l,int r);
int query(int x,int l,int r,int ql,int qr);
void update(int x,int l,int r,int ul,int ur,int val);
void pushdown(int x,int len);
void pushup(int x);
void build(int x,int l,int r)
{
    if(l==r)  {tree[x].val=1;return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(l>qr||r<ql) return 0;
    if(ql<=l&&qr>=r) return tree[x].val;
    pushdown(x,r-l+1);
    int mid=(l+r)>>1;
    return query(x<<1,l,mid,ql,qr)+query(x<<1|1,mid+1,r,ql,qr);
}
void update(int x,int l,int r,int ul,int ur,int val)
{
    if(l>ur||r<ul) return;
    if(ul<=l&&ur>=r)
    {
        tree[x].lazy=val;
        tree[x].val=val*(r-l+1);
        return;
    }
    pushdown(x,r-l+1);
    int mid=(l+r)>>1;
    if(ul<=mid) update(x<<1,l,mid,ul,ur,val);
    if(ur>mid) update(x<<1|1,mid+1,r,ul,ur,val);
    pushup(x);
}
inline void pushdown(int x,int len)
{
    if(tree[x].lazy)
    {
        tree[x<<1].lazy=tree[x<<1|1].lazy=tree[x].lazy;
        tree[x<<1].val=tree[x].lazy*(len-(len>>1));
        tree[x<<1|1].val=tree[x].lazy*(len>>1);
        tree[x].lazy=0;
    }
}
inline void pushup(int x)
{
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
}
int main()
{
    int t,n,q,a,b,c;
    scanf("%d",&t);
    for(int T=1;T<=t;T++)
    {
        scanf("%d",&n);
        memset(tree,0,sizeof(tree));
        build(1,1,n);
        scanf("%d",&q);
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            update(1,1,n,a,b,c);
        }
        printf("Case %d: The total value of the hook is %d.\n",T,query(1,1,n,1,n));
    }
}
