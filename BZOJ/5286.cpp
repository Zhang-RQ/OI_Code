#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1E5+10;
const int INF=1<<30;
struct node{
    int mx,l_ans;
}t[MAXN<<3];
int a[MAXN],n,m,q,lstans;
int calc(int x,int l,int r,int k)
{
    if(l==r) return t[x].mx>k?l+k:INF;
    if(t[x<<1|1].mx<k) return calc(x<<1,l,(l+r)>>1,k);
    else return min(t[x].l_ans,calc(x<<1|1,((l+r)>>1)+1,r,k));
}
void pushup(int x,int l,int r) {t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);t[x].l_ans=calc(x<<1,l,(l+r)>>1,t[x<<1|1].mx);}
void build(int x,int l,int r)
{
    if(l==r) return t[x].mx=a[l]-l,void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x,l,r);
}
void change(int x,int l,int r,int pos,int v)
{
    if(l==r) return t[x].mx=v-l,void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos,v);
    else change(x<<1|1,mid+1,r,pos,v);
    pushup(x,l,r);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(1,1,n);
    printf("%d\n",lstans=calc(1,1,n,t[1].mx-n)+n);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        if(q) x^=lstans,y^=lstans;
        change(1,1,n,x,y);
        printf("%d\n",lstans=calc(1,1,n,t[1].mx-n)+n);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}