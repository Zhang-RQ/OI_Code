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
#define MAXN 200100
using namespace std;
typedef long long ll;
int tree[MAXN<<2],arr[MAXN];
void build(int x,int l,int r)
{
    if(l==r) {tree[x]=arr[l];return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build((x<<1)+1,mid+1,r);
    tree[x]=max(tree[x<<1],tree[(x<<1)+1]);
}
void update(int x,int l,int r,int pos,int val)
{
    if(l==r) {tree[x]=val;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) update(x<<1,l,mid,pos,val);
    else update((x<<1)+1,mid+1,r,pos,val);
    tree[x]=max(tree[x<<1],tree[(x<<1)+1]);
}
int query(int x,int l,int r,int ql,int qr)
{
    if(ql>r||qr<l) return 0xcfcfcfcf;
    else if(l>=ql&&r<=qr) return tree[x];
    int mid=(l+r)>>1;
    return max(query(x<<1,l,mid,ql,qr),query((x<<1)+1,mid+1,r,ql,qr));
}
int main()
{
    int n,m,a,b;
    char str[10];
    while(~scanf("%d%d",&n,&m))
    {
        memset(arr,0,sizeof(arr));
        memset(tree,0,sizeof(tree));
        for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
        build(1,1,n);
        for(int i=1;i<=m;i++)
        {
            scanf("%s",str+1);
            scanf("%d%d",&a,&b);
            if(str[1]=='Q') printf("%d\n",query(1,1,n,a,b));
            if(str[1]=='U') update(1,1,n,a,b);
        }
    }
}
