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
#define MAXN 50010
using namespace std;
typedef long long ll;
int segtree[MAXN*4];
int arr[MAXN];
void build(int x,int tl,int tr)
{
    if(tl==tr)
    {
        segtree[x]=arr[tl];
    }else{
        int mid=(tl+tr)>>1;
        build(x<<1,tl,mid);
        build((x<<1)+1,mid+1,tr);
        segtree[x]=segtree[x<<1]+segtree[(x<<1)+1];
    }
}
void add(int val,int x,int pos,int tl,int tr)
{
    if(tl==tr) {segtree[x]+=val;return;}
    int mid=(tl+tr)>>1;
    if(pos<=mid) add(val,x<<1,pos,tl,mid);
    else add(val,(x<<1)+1,pos,mid+1,tr);
    segtree[x]=segtree[x<<1]+segtree[(x<<1)+1];
}
int query(int x,int l,int r,int tl,int tr)// l...r查询区间
{
        if(tl>r||tr<l) return 0;
        if(tl>=l&&tr<=r) return segtree[x];
        int mid=(tl+tr)>>1;
        return query(x<<1,l,r,tl,mid)+query((x<<1)+1,l,r,mid+1,tr);
}
int main()
{
    int T,n,a,b,temp;
    char str[10];
    scanf("%d",&T);
    temp=T;
    while(T--)
    {
        memset(segtree,0,sizeof(segtree));
        memset(arr,0,sizeof(arr));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)   scanf("%d",&arr[i]);
        build(1,1,n);
        printf("Case %d:\n",temp-T);
        while(scanf("%s",str+1)&&str[1]!='E')
        {
            scanf("%d%d",&a,&b);
            if(str[1]=='Q') printf("%d\n",query(1,a,b,1,n));
            else if(str[1]=='A') add(b,1,a,1,n);
            else if(str[1]=='S') add(-b,1,a,1,n);
        }
    }
}
