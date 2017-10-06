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
#define MAXN 300010
using namespace std;
typedef long long ll;

int tree[MAXN<<2];
int h,w,n;
void build(int x,int l,int r);
inline void pushup(int x);
int query(int x,int l,int r,int val);
int main()
{
    int a;
    while(~scanf("%d%d%d",&h,&w,&n))
    {
        int len=min(n,h);
        memset(tree,0,sizeof(tree));
        build(1,1,len);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a);
            if(a>tree[1]) {printf("-1\n");continue;}
            printf("%d\n",query(1,1,len,a));
        }
    }
}

void build(int x,int l,int r)
{
    if(l==r) {tree[x]=w;return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
inline void pushup(int x)
{
    tree[x]=max(tree[x<<1],tree[x<<1|1]);
}
int query(int x,int l,int r,int val)
{
    if(l==r)
    {
        tree[x]-=val;
        return l;
    }
    int mid=(l+r)>>1;
    int ret;
    if(tree[x<<1]>=val) ret=query(x<<1,l,mid,val);
    else ret=query(x<<1|1,mid+1,r,val);
    pushup(x);
    return ret;
}
