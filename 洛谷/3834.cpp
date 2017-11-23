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
#define Ls tree[x].ls,l,mid
#define Rs tree[x].rs,mid+1,r
struct node{
    int val,ls,rs;
}tree[5000010];
int cnt=0,rt[500010];
void insert(int &x,int l,int r,int x_,int pos)
{
    x=++cnt;
    tree[x]=tree[x_];
    tree[x].val++;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(pos<=mid)
        insert(Ls,tree[x_].ls,pos);
    else
        insert(Rs,tree[x_].rs,pos);
}
int query(int x,int l,int r,int x_,int k)
{
    if(l==r)
        return l;
    int val=tree[tree[x].ls].val-tree[tree[x_].ls].val;
    int mid=(l+r)>>1;
    if(val>=k)
        return query(Ls,tree[x_].ls,k);
    else return query(Rs,tree[x_].rs,k-val);
}
int arr[500010];
int arr1[500010];
int n,q,ll,rr,k;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]),
        arr1[i]=arr[i];
    sort(arr1+1,arr1+1+n);
    int tot=unique(arr1+1,arr1+1+n)-arr1-1;
    for(int i=1;i<=n;i++)
        arr[i]=lower_bound(arr1+1,arr1+1+tot,arr[i])-arr1;
    for(int i=1;i<=n;i++)
        insert(rt[i],1,n,rt[i-1],arr[i]);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d%d",&ll,&rr,&k);
        printf("%d\n",arr1[query(rt[rr],1,n,rt[ll-1],k)]);
    }
}
