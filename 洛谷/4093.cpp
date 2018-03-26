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
const int MAXN=1E5+10;
struct data{int v,l,r,id;} b[MAXN],tp[MAXN];
int dp[MAXN];
int n,x,y,m,t[MAXN];
void change(int pos,int val)
{
    for(int i=pos;i<MAXN;i+=i&-i)
        t[i]=max(t[i],val);
}
int query(int pos)
{
    int ret=0;
    for(int i=pos;i>=1;i-=i&-i)
        ret=max(ret,t[i]);
    return ret;
}
void clear(int pos)
{
    for(int i=pos;i<MAXN;i+=i&-i)
        t[i]=0;
}
bool cmp1(data a,data b) {return a.v<b.v;}
bool cmp2(data a,data b) {return a.r<b.r;}
bool cmp3(data a,data b) {return a.id<b.id;}
void CDQ(int l,int r)
{
    if(l==r)  {dp[b[l].id]=max(dp[b[l].id],1);return;}
    int mid=(l+r)>>1;
    CDQ(l,mid);
    int L=l,R=mid+1,cnt=0;
    sort(b+l,b+mid+1,cmp2);sort(b+mid+1,b+r+1,cmp1);
    while(L<=mid&&R<=r)
    {
        if(b[L].r<=b[R].v)  change(b[L].v,dp[b[L].id]),tp[++cnt]=b[L++];
        else dp[b[R].id]=max(dp[b[R].id],query(b[R].l)+1),tp[++cnt]=b[R++];
    }
    while(L<=mid)  tp[++cnt]=b[L++];
    while(R<=r)    dp[b[R].id]=max(dp[b[R].id],query(b[R].l)+1),tp[++cnt]=b[R++];
    for(int i=l;i<=mid;i++) clear(b[i].v);
    for(int i=l;i<=r;i++)  b[i]=tp[i-l+1];
    sort(b+l,b+r+1,cmp3);
    CDQ(mid+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i].v),b[i].l=b[i].r=b[i].v,b[i].id=i;
    for(int i=1;i<=m;i++)
        scanf("%d%d",&x,&y),
        b[x].r=max(b[x].r,y),
        b[x].l=min(b[x].l,y);
    CDQ(1,n);
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
    printf("%d\n",ans);
}
