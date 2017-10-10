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
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
#define MAXN 500100
using namespace std;
typedef long long ll;
int tree[MAXN<<2];
int arr[MAXN];
inline void pushup(int x)
{
    tree[x]=tree[x<<1]+tree[x<<1|1];
}
void build(int x,int l,int r)
{
    if(l==r) {tree[x]=arr[l];return;}
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    pushup(x);
}
void edit(int x,int l,int r,int pos,int val)
{
    if(l==r) {tree[x]+=val;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) edit(Ls,pos,val);
    else edit(Rs,pos,val);
    pushup(x);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return tree[x];
    if(ql>r||qr<l) return 0;
    int mid=(l+r)>>1;
    return query(Ls,ql,qr)+query(Rs,ql,qr);
}
int n,m,ops,t1,t2;
int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        cin>>ops>>t1>>t2;
        if(ops==1) edit(1,1,n,t1,t2);
        else printf("%d\n",query(1,1,n,t1,t2));
    }
}
