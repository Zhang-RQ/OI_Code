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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=500010;
int siz[MAXN],d[MAXN],n;
double k;
int mn[MAXN<<3],tag[MAXN<<3],fa[MAXN],ans[MAXN],cnt[MAXN];
bool cmp(const int &lhs,const int &rhs) {return lhs>rhs;}
void pushup(int x) {mn[x]=min(mn[x<<1],mn[x<<1|1]);}
void pushdown(int x)
{
    if(tag[x])
    {
        mn[x<<1]+=tag[x];mn[x<<1|1]+=tag[x];
        tag[x<<1]+=tag[x];tag[x<<1|1]+=tag[x];
        tag[x]=0;
    }
}
void build(int x,int l,int r)
{
    if(l==r) {mn[x]=l;return;}
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}
void change(int x,int l,int r,int cl,int cr,int val)
{
    if(cl<=l&&r<=cr) {mn[x]+=val;tag[x]+=val;return;}
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(x<<1,l,mid,cl,cr,val);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr,val);
    pushup(x);
}
int query(int x,int l,int r,int k)
{
    if(l==r) return mn[x]>=k?l:l+1;
    pushdown(x);
    int mid=(l+r)>>1;
    if(mn[x<<1|1]>=k) return query(x<<1,l,mid,k);
    else return query(x<<1|1,mid+1,r,k);
}
int main()
{
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    sort(d+1,d+1+n,cmp);
    for(int i=n-1;i>=1;i--)
        if(d[i]==d[i+1]) cnt[i]=cnt[i+1]+1;
        else cnt[i]=0;
    for(int i=n;i>=1;i--) fa[i]=(int)(i/k),siz[i]=1;
    for(int i=n;i>=1;i--) siz[fa[i]]+=siz[i];
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        if(fa[i]&&fa[i]!=fa[i-1]) change(1,1,n,ans[fa[i]],n,siz[fa[i]]-1);
        int x=query(1,1,n,siz[i]);
        x+=cnt[x];cnt[x]++;
        x-=(cnt[x]-1);ans[i]=x;
        change(1,1,n,x,n,-siz[i]);
    }
    for(int i=1;i<=n;i++) printf("%d ",d[ans[i]]);
    puts("");
}
