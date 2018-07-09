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

const int MAXK=60;
const int P=1E9+7;

ll n,m,M;
ll f[MAXK],g[MAXK],tmp[MAXK],ans[MAXK];
ll inv[MAXK],a[MAXK];

inline ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

inline void Lagrange_interpolation() //-> ans
{
    memset(f,0,sizeof f);memset(ans,0,sizeof ans);
    f[0]=1;
    for(int i=1;i<=m+3;i++)
    {
        for(int j=m+3;j>=1;j--)
            f[j]=f[j]*(P-i)%P,f[j]=(f[j]+f[j-1])%P;
        f[0]=f[0]*(P-i)%P;
    }
    for(int i=1;i<=m+3;i++)
    {
        memcpy(tmp,f,sizeof f);
        for(int j=0;j<=m+2;j++)
            tmp[j]=P-tmp[j]*inv[i]%P,tmp[j+1]=(tmp[j+1]-tmp[j]+P)%P;
        ll invv=1;
        for(int j=1;j<=m+3;j++)
            if(j!=i)
            {
                if(j>i) invv=(P-invv*inv[j-i]%P)%P;
                else invv=invv*inv[i-j]%P;
            }
        for(int j=0;j<=m+2;j++)
            (ans[j]+=tmp[j]*g[i]%P*invv%P)%=P;
    }
}

ll fx(ll x)
{
    ll ret=0;x%=P;
    for(int i=0;i<=M;i++)
        (ret+=ans[i]*ksm(x,i)%P)%=P;
    return ret;
}

void solve()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m+3;i++) g[i]=(g[i-1]+ksm(i,m+1))%P;
    Lagrange_interpolation();
    a[++m]=++n;
    sort(a+1,a+1+m);
    ll res=0;M=m+1;
    for(int i=1;i<M;i++)
    {
        (res+=fx(n))%=P;
        for(int j=1;j<=m;j++)
            res=(res-ksm(a[j],M-1)+P)%P;
        ll t=a[1];n-=t;
        for(int j=1;j<m;j++)
            a[j]=a[j+1]-t;
        --m;
    }
    printf("%lld\n",res);
}

int main()
{
    for(int i=1;i<=59;i++) inv[i]=ksm(i,P-2);
    int T;
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}