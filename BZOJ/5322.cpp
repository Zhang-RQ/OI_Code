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
const int MAXN=1.2E7+10;
const int MAXM=1E6+10;
const int P=998244353;
ll fac[MAXN],ifac[MAXN];
int lstmax,n,m,l,r,a[MAXM],q[MAXM];
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}
void init(int lim)
{
    if(lim<=lstmax) return;
    for(int i=lstmax+1;i<=lim;i++)
        fac[i]=(fac[i-1]*i)%P;
    ifac[lim]=ksm(fac[lim],P-2);
    for(int i=lim-1;i>=lstmax;i--)
        ifac[i]=ifac[i+1]*(i+1)%P;
    lstmax=lim;
}
void solve()
{
    scanf("%d%d%d%d",&n,&m,&l,&r);
    init(n+m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    int lst=1,siz=0,_m=m;
    ll ans=1;
    for(int i=2;i<=n;i++)
        if(a[i]!=a[i-1])
        {
            if(a[lst]>=l&&a[lst]<=r) q[++siz]=i-lst;
            else (ans*=fac[i-lst])%=P;
            lst=i;
        }
    if(a[lst]>=l&&a[lst]<=r) q[++siz]=n-lst+1;
    else (ans*=fac[n-lst+1])%=P;
    sort(q+1,q+siz+1);
    ll tot=r-l+1-siz;
    ll lsth=0;lst=siz+1;
    for(int i=1;i<=siz;i++)
    {
        ll v=q[i];
        if((v-lsth)*tot<=m)
        {
            m-=(v-lsth)*tot;
            (ans*=ksm(ifac[lsth]*fac[v]%P,tot))%=P;
            (ans*=fac[v])%=P;
            tot++;lsth=v;
        }
        else
        {
            ll A=m/tot,B=m%tot;
            (ans*=ksm(ifac[lsth]*fac[lsth+A]%P,tot-B))%=P;
            (ans*=ksm(ifac[lsth]*fac[lsth+A+1]%P,B))%=P;
            (ans*=fac[v])%=P;
            m=0;
            lst=i+1;
            break;
        }
    }
    if(m)
    {
        ll A=m/tot,B=m%tot;
        (ans*=ksm(ifac[lsth]*fac[lsth+A]%P,tot))%=P;
        (ans*=ksm((lsth+A+1)%P,B))%=P;
    }
    else
        while(siz>=lst)
            (ans*=fac[q[siz--]])%=P;
    printf("%lld\n",fac[n+_m]*ksm(ans,P-2)%P);
}
signed main()
{
    int T;fac[0]=1;
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}