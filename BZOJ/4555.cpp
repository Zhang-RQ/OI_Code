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
const int P=998244353;
const int g=3;
const int N=262440<<3;
const int MAXN=100010<<2;
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
int rev[N];
void NTT(ll *a,int n,int f)
{
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,f?(P-1)/i:(P-1)-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k]%P,t=a[j+k+(i>>1)]*w%P;
                a[j+k]=(u+t)%P;
                a[j+k+(i>>1)]=(u-t+P)%P;
                w=w*wn%P;
            }
        }
    }
}
ll fac[MAXN],ifac[MAXN],pw2[MAXN],a[MAXN],b[MAXN],c[MAXN],ans;
int n,tot=1,lg2=0,inv;
int main()
{
    scanf("%d",&n);
    fac[0]=ifac[0]=pw2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
    ifac[n]=ksm(fac[n],P-2);
    for(int i=n-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%P;
    for(int i=1;i<=n;i++) pw2[i]=pw2[i-1]*2%P;
    for(int i=0;i<=n;i++) a[i]=(i&1?-1:1)*ifac[i];
    b[0]=1;b[1]=(n+1)%P;
    for(int i=2;i<=n;i++) b[i]=((ksm(i,n+1)-1)%P*ksm(i-1,P-2)%P+P)%P*ifac[i]%P;
    while(tot<=n+n+2) tot<<=1,lg2++;
    for(int i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    NTT(a,tot,1);NTT(b,tot,1);
    for(int i=0;i<tot;i++) c[i]=a[i]*b[i]%P;
    NTT(c,tot,0);
    inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++) (c[i]*=inv)%=P;
    for(int i=0;i<=n;i++) (ans+=pw2[i]*fac[i]%P*c[i]%P)%=P;
    printf("%lld\n",ans);
}
