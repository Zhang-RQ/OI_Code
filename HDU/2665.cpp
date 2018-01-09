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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
struct node{
    int val,ls,rs;
}tree[400000];
int cnt;
int rt[100010];
void insert(int &x,int l,int r,int pos,int x_)
{
    x=++cnt;
    tree[x]=tree[x_];
    tree[x].val++;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(tree[x].ls,l,mid,pos,tree[x_].ls);
    else insert(tree[x].rs,mid+1,r,pos,tree[x_].rs);
}
int query(int x,int l,int r,int x_,int k)
{
    if(l==r) return l;
    int tmp=tree[tree[x].ls].val-tree[tree[x_].ls].val;
    int mid=(l+r)>>1;
    if(tmp>=k) return query(tree[x].ls,l,mid,tree[x_].ls,k);
    else return query(tree[x].rs,mid+1,r,tree[x_].rs,tmp-k);
}
int n,arr[1000010],arr1[100010],m,x,y,z;
int T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(tree,0,sizeof tree);
        memset(rt,0,sizeof rt);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&arr1[i]),arr[i]=arr1[i];
        sort(arr1+1,arr1+1+n);
        int tot=unique(arr1+1,arr1+1+n)-arr1-1;
        for(int i=1;i<=n;i++)
            arr[i]=lower_bound(arr1+1,arr1+1+tot,arr[i])-arr1;
        for(int i=1;i<=n;i++)
            insert(rt[i],1,n,arr[i],rt[i-1]);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&x,&y,&z),
            printf("%d\n",arr1[query(rt[y],1,tot,rt[x-1],z) ]);
    }
}
