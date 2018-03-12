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
const int MAXN=1000005;
ll fac[MAXN],ifac[MAXN],siz[MAXN<<1],f[MAXN];
int P,n;
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret;
}
void init()
{
    fac[0]=1;
    for(int i=1;i<min(MAXN,P);i++)
        fac[i]=(fac[i-1]*i)%P;
    ifac[min(MAXN,P)-1]=ksm(fac[min(MAXN,P)-1],P-2);
    for(int i=min(MAXN,P)-2;~i;i--)
        ifac[i]=ifac[i+1]*(i+1)%P;
}
ll Lucas(int n,int m)
{
    if(n<m) return 0;
    if(n==m||m==0) return 1;
    if(n<P&&m<P) return fac[n]*ifac[m]%P*ifac[n-m]%P;
    return Lucas(n%P,m%P)*Lucas(n/P,m/P)%P;
}
int main()
{
    scanf("%d%d",&n,&P);
    init();
    for(int i=n;i;i--)
    {
        siz[i]=siz[i<<1]+siz[i<<1|1]+1;
        f[i]=(((i<<1)>n?1ll:f[i<<1])*((i<<1|1)>n?1ll:f[i<<1|1]))%P*Lucas(siz[i]-1,siz[i<<1])%P;
    }
    printf("%lld\n",f[1]%P);
}
