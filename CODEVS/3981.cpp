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
#define MAXN 200010
#define Ls x<<1,l,mid
#define Rs x<<1|1,mid+1,r
using namespace std;
typedef long long ll;
struct node{
    ll lsum,rsum,val,sum;
}tree[MAXN<<2];
int arr[MAXN];
int main()
{

}

inline void pushup(int x)
{
    tree[x].val=tree[x<<1].val+tree[x<<1|1].val;
    tree[x].lsum=max(tree[x<<1].lsum,tree[x<<1].val+tree[x<<1|1].lsum);
    tree[x].rsum=max(tree[x<<1|1].rsum,tree[x<<1|1].val+tree[x<<1].rsum);
    tree[x].sum=max(max(tree[x<<1].sum,tree[x<<1|1].sum),tree[x<<1].rsum+tree[x<<1|1].lsum);
}

void build (int x,int l,int r)
{
    if(l==r)
    {
        tree[x].val=tree[x].lsum=tree[x].rsum=tree[x].sum=arr[l];
        return;
    }
    int mid=(l+r)>>1;
    build(Ls);
    build(Rs);
    pushup(x);
}

node query(int x,int l,int r,int ql,int qr)
{
    if(l==ql&&r==qr) return tree[x];
    int mid=(l+r)>>1;
    node ans;
    if(qr<=mid) query(Ls,ql,qr);
    else if(ql>mid) query(Rs,ql,qr);//notice
    else{
        node tl=query(Ls,ql,qr);
        node rl=query(Rs,ql,qr);
        ans.lsum=max(tl.lsum,tl.val+rl.lsum);
        ans.rsum=max(rl.rsum,rl.val+rl.rsum);
        ans.sum=max(max(tl.sum,rl.sum),tl.rsum+rl.lsum);
    }
    return ans;
}
