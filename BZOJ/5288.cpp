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
const int MAXN=1E6+10;
int t[MAXN<<3],key[MAXN],n,m,p,top,stk[MAXN];
int lS[MAXN],rS[MAXN],l[MAXN],r[MAXN];
void build(int x,int l,int r)
{
    if(l==r) return t[x]=key[l],void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    t[x]=max(t[x<<1],t[x<<1|1]);
}
int Get(int x,int l,int r,int k)
{
    if(t[x]<=k) return 0;
    if(l==r) return l;
    int mid=(l+r)>>1;
    return t[x<<1|1]>k?Get(x<<1|1,mid+1,r,k):Get(x<<1,l,mid,k);
}
int Query(int x,int l,int r,int ql,int qr,int k)
{
    if(ql<=l&&r<=qr) return Get(x,l,r,k);
    int mid=(l+r)>>1,ret=0;
    if(qr>mid) ret=Query(x<<1|1,mid+1,r,ql,qr,k);
    if(ret) return ret;
    if(ql<=mid) ret=Query(x<<1,l,mid,ql,qr,k);
    return ret;
}
int find_pos(int l,int r,int k)
{
    if(l>r) return l;
    int pos=Query(1,1,n,l,r,k);
    return pos?pos+1:l;
}
void init()
{
    build(1,1,n);
    key[0]=-1;key[n]=n+1;
    for(int i=1;i<=n;i++) lS[i]=key[i-1]&&key[i-1]<=i-1?i:lS[i-1];
    for(int i=n;i>=1;i--) rS[i]=key[i+1]&&key[i+1]>=i+1?i:rS[i+1];
    for(int i=n;i>=1;i--)
    {
        l[i]=r[i]=i;
        l[i]=find_pos(lS[i],l[i]-1,r[i]);
        stk[++top]=i;
        while(top&&((l[i]<=key[stk[top]]&&key[stk[top]]<=r[i])||!key[stk[top]]))
        {
            r[i]=stk[--top];
            l[i]=find_pos(lS[i],l[i]-1,r[i]);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        key[x]=y;
    }
    init();
    for(int i=1,x,y;i<=p;i++)
    {
        scanf("%d%d",&x,&y);
        puts(l[x]<=y&&y<=r[x]?"YES":"NO");
    }
    #ifdef LOCAL
        system("pause");
    #endif
}