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

const int MAXN=100010;

int n,T,P;
pair<int,int> Q[MAXN];
ll t[MAXN<<2];

void build(int x,int l,int r)
{
    if(l==r) return t[x]=Q[l].first==1?Q[l].second:1,void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    t[x]=t[x<<1]*t[x<<1|1]%P;
}

void change(int x,int l,int r,int pos)
{
    if(l==r) return t[x]=1,void();
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos);
    else change(x<<1|1,mid+1,r,pos);
    t[x]=t[x<<1]*t[x<<1|1]%P;
}

ll query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;ll ret=1;
    if(ql<=mid) ret*=query(x<<1,l,mid,ql,qr);
    if(qr>mid)  ret*=query(x<<1|1,mid+1,r,ql,qr);
    return ret%P;
}

inline void solve()
{
    scanf("%d%d",&n,&P);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&Q[i].first,&Q[i].second);
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        if(Q[i].first==1)  printf("%lld\n",query(1,1,n,1,i));
        else change(1,1,n,Q[i].second),printf("%lld\n",query(1,1,n,1,i));
    }
}

int main()
{
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}