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

const int P=1E9+7;
const int MAXN=410;

int a[MAXN],n,q;
int f[MAXN][MAXN],suml[MAXN][MAXN],sumr[MAXN][MAXN];

ll calc(int l,int r)
{
    assert(l<=r);
    return (1ll*(r-l+1)*(r-l+2)/2%P+1ll*l*(l-1)/2%P+1ll*(n-r)*(n-r+1)/2%P)%P;
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int l=1;l<=n;l++)
        for(int r=l;r<=n;r++)
        {
            int mx=0,mn=1<<30;
            for(int i=l;i<=r;i++)
                mx=max(mx,a[i]);
            if(l>1) mn=min(mn,a[l-1]);
            if(r<n) mn=min(mn,a[r+1]);
            if(mx<mn)
            {
                if(mn==1<<30) f[l][r]=mx;
                else f[l][r]=P-mn+mx;
            }
        }
    for(int i=1;i<=q;i++)
    {
        for(int r=1;r<=n;r++)
            for(int l=1;l<r;l++)
                suml[l][r]=(suml[l-1][r]+1ll*f[l][r]*(l-1)%P)%P;
        for(int l=1;l<=n;l++)
            for(int r=n;r>l;r--)
                sumr[l][r]=(sumr[l][r+1]+1ll*f[l][r]*(n-r)%P)%P;
        for(int l=1;l<=n;l++)
            for(int r=l;r<=n;r++)
                f[l][r]=(calc(l,r)*f[l][r]%P+suml[l-1][r]+sumr[l][r+1])%P;
    }
    for(int i=1,ans=0;i<=n;i++)
    {
        ans=0;
        for(int l=i;l>=1;l--)
            for(int r=i;r<=n;r++)
                (ans+=f[l][r])%=P;
        printf("%d%c",ans,i==n?'\n':' ');
    }
    #ifdef LOCAL
        system("pause");
    #endif
}