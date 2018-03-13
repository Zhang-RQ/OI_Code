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
const int MAXN=2000100;
const int P=20100403;
ll fac[MAXN],ifac[MAXN];
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
    for(int i=1;i<MAXN;i++)
        fac[i]=fac[i-1]*i%P;
    ifac[MAXN-1]=ksm(fac[MAXN-1],P-2);
    for(int i=MAXN-2;~i;i--)
        ifac[i]=ifac[i+1]*(i+1)%P;
}
ll C(int n,int m)
{
    if(n<m) return 0;
    return fac[n]*ifac[m]%P*ifac[n-m]%P;
}
int n,m;
int main()
{
    init();
    scanf("%d%d",&n,&m);
    ll ans=(C(n+m,m)-C(n+m,m-1)+P)%P;
    printf("%lld\n",ans);
}
