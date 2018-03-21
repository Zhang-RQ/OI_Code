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
const int MAXN=1048576;
int rev[MAXN];
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
                a[j+k]=(u+t)%P;a[j+k+(i>>1)]=(u-t+P)%P;
                w=w*wn%P;
            }
        }
    }
}
ll s[MAXN],t1[MAXN],t2[MAXN],fac[MAXN],ifac[MAXN],ans,C[MAXN],inv[MAXN];
int n,k,tot=1,lg2;
int main()
{
    scanf("%d%d",&n,&k);n--;
    while(tot<=k+k+2) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    fac[0]=ifac[0]=inv[1]=1;
    for(int i=2;i<=k;i++)
        inv[i]=(P-(P/i)*inv[P%i]%P)%P;
    C[0]=1;
    for(int i=1;i<=k;i++)
        C[i]=C[i-1]*(n-i+1)%P*inv[i]%P;
    for(int i=1;i<=k;i++)
        fac[i]=fac[i-1]*i%P;
    ifac[k]=ksm(fac[k],P-2);
    for(int i=k-1;i>=1;i--)
        ifac[i]=ifac[i+1]*(i+1)%P;
    // printf("%lld==%lld %lld\n",ifac[3],inv[6],fac[2]);
    for(int i=0;i<tot;i++)
        t1[i]=(P+(i&1?-1:1)*ifac[i])%P,
        t2[i]=ksm(i,k)*ifac[i]%P;
    NTT(t1,tot,1);NTT(t2,tot,1);
    for(int i=0;i<tot;i++)
        s[i]=t1[i]*t2[i]%P;
    NTT(s,tot,0);
    int inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++)
        (s[i]*=inv)%=P;
    // for(int i=0;i<tot;i++)
    //     printf("%lld ",s[i]);
    // puts("");
    for(int i=0;i<=min(n,k);i++)
        (ans+=s[i]*fac[i]%P*C[i]%P*ksm(2,n-i)%P)%=P;
    ans=ans*(n+1)%P*ksm(2,(1ll*n*(n-1)/2)%(P-1))%P;
    printf("%lld\n",ans);
}
