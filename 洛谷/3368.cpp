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
#define MAXN 500010
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
using namespace std;
typedef long long ll;
struct node{
    int val,tag;
}tree[MAXN<<2];
int arr[MAXN];
int n,m,x,y,k,ops;
inline void pushup(int x)
{
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
}
void build(int x,int l,int r)
{
    if(l==r) {tree[x].val=arr[l];return;}
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    pushup(x);
}inline void pushdown(int x,int l,int r)
{
    if(tree[x].tag)
    {
        int mid=(l+r)>>1;
        tree[x<<1].tag+=tree[x].tag;
        tree[x<<1|1].tag+=tree[x].tag;
        tree[x<<1].val+=tree[x].tag*(mid-l+1);
        tree[x<<1|1].val+=tree[x].tag*(r-mid);
        tree[x].tag=0;
    }
}
int query(int x,int l,int r,int pos)
{
    if(l==r) return tree[x].val;
    int mid=(l+r)>>1;
    tree[x].val+=tree[x].tag*(r-l+1);
    pushdown(x,l,r);
    if(pos<=mid) return query(Ls,pos);
    else return query(Rs,pos);
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&cr>=r)
    {
        tree[x].val+=val*(r-l+1);
        tree[x].tag+=val;
        return;
    }
    else if(cl>r||cr<l) return;
    int mid=(l+r)>>1;
    if(cr>mid) change(Rs,cl,cr,val);
    if(cl<=mid) change(Ls,cl,cr,val);
    pushdown(x,l,r);
    pushup(x);
    return;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&ops);
        if(ops==1)
        {
            scanf("%d%d%d",&x,&y,&k);
            change(1,1,n,x,y,k);
        }
        if(ops==2)
        {
            scanf("%d",&x);
            printf("%d\n",query(1,1,n,x));
        }
    }
}
