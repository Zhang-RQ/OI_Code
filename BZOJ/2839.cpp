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
const int P=1000000007;
const int MAXN=1000002;
ll fac[MAXN],ifac[MAXN],pow2[MAXN];
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
    fac[0]=1;pow2[0]=1;
    for(int i=1;i<MAXN;i++)
        pow2[i]=(pow2[i-1]<<1)%(P-1);
    for(int i=1;i<MAXN;i++)
        fac[i]=(fac[i-1]*i)%P;
    ifac[MAXN-1]=ksm(fac[MAXN-1],P-2);
    for(int i=MAXN-2;~i;i--)
        ifac[i]=ifac[i+1]*(i+1)%P;
}
ll C(int n,int m)
{
    if(n<m) return 0;
    return fac[n]*ifac[m]%P*ifac[n-m]%P;
}
int n,k;
int main()
{
    init();
    scanf("%d%d",&n,&k);
    ll ans=ksm(2,pow2[n-k]);
    for(int i=1,f=-1;i<=n;i++,f=-f)
        (ans+=C(n-k,i)*ksm(2,pow2[n-k-i])%P*f+P)%=P;
    (ans+=P)%=P;
     ans*=C(n,k);
    printf("%lld\n",ans%P);
}
