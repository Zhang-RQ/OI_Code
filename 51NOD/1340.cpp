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
typedef __int128 lll;
using namespace std;

const ll INF=1ll<<60;
const int MAXN=55;
#define f(i,j,k) f[i][j][k+MAXN]

int n,m1,m2;
lll f[MAXN][MAXN][MAXN<<1];

inline void add(int u,int v,int w1,int w2) // u ->v w1*x+w2
{
    f(u,v,w1)=min(f(u,v,w1),(lll)w2);
}

void solve()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=-n;k<=n;k++)
                f(i,j,k)=INF;
    for(int i=1;i<=n;i++)
    {
        int j=i%n+1;
        add(j,i,j<i,-1);
    }
    for(int i=1,a,b,d;i<=m1;i++)
    {
        scanf("%d%d%d",&a,&b,&d);
        ++a;++b;
        if(a<b) add(b,a,0,-d);
        else add(b,a,1,-d);
    }
    for(int i=1,a,b,d;i<=m2;i++)
    {
        scanf("%d%d%d",&a,&b,&d);
        ++a;++b;
        if(a<b) add(a,b,0,d);
        else add(a,b,-1,d);
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int l=-n;l<=n;l++)
                if(f(i,k,l)!=INF)
                    for(int j=1;j<=n;j++)
                        for(int r=max(-n,-n-l);r<=min(n,n-l);r++)
                           if(f(k,j,r)!=INF) f(i,j,l+r)=min(f(i,j,l+r),f(i,k,l)+f(k,j,r));
    lll mn=0,mx=INF;
    for(int i=1;i<=n;i++)
        for(int k=-n;k<=n;k++)
        {
            if(f(i,i,k)==INF) continue;
            if(k<0) mx=min(mx,-f(i,i,k)/k);
            if(k==0&&f(i,i,k)<0) mn=mx+1;
            if(k>0) mn=max(mn,(-f(i,i,k)-1)/k+1);
        }
    lll ans=mx-mn+1;
    if(mx>=INF) puts("-1");
    else if(mn>mx) puts("0");
    else printf("%lld\n",(ll)ans);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--) solve();
    #ifdef LOCAL
        system("pause");
    #endif
}