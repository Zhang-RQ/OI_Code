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
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
using namespace std;
typedef long long ll;
struct node{
    ll val,tag;
}tree[MAXN<<2];
ll arr[MAXN];
inline void pushup(int x)
{
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
}
inline void pushdown(int x,int l,int r)
{
    if(tree[x].tag)
    {
        int mid=(l+r)>>1;
        tree[x<<1].val+=tree[x].tag*(mid-l+1);
        tree[x<<1|1].val+=tree[x].tag*(r-mid);
        tree[x<<1].tag+=tree[x].tag;
        tree[x<<1|1].tag+=tree[x].tag;
        tree[x].tag=0;
    }
}
void build(int x,int l,int r)
{
    if(l==r) {tree[x].val=arr[l];return;}
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    pushup(x);
}
ll query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return tree[x].val;
    if(ql>r||qr<l) return 0;
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    return query(Ls,ql,qr)+query(Rs,ql,qr);
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&cr>=r) {tree[x].val+=val*(r-l+1);tree[x].tag+=val;return;}
    if(cl>r||cr<l) return;
    int mid=(l+r)>>1;
    pushdown(x,l,r);
    if(cl<=mid) change(Ls,cl,cr,val);
    if(cr>mid)  change(Rs,cl,cr,val);
    pushup(x);
}
int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    int ops,t1,t2,t3;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        cin>>ops;
        if(ops==1)
        {
            cin>>t1>>t2>>t3;
            change(1,1,n,t1,t2,t3);
        }
        else
        {
            cin>>t1>>t2;
            cout<<query(1,1,n,t1,t2)<<endl;
        }
    }
}
