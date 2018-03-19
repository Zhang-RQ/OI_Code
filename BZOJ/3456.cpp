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
const int P=1004535809;
const int g=3;
const int MAXN=262440;
int rev[MAXN];
ll w[MAXN],dp[MAXN],tp1[MAXN],tp2[MAXN],tp3[MAXN],ifac[MAXN],fac[MAXN];
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
void _NTT(ll *a,int n,bool flag)
{
    for(int i=0;i<n;i++)
        if(i>rev[i]) swap(a[rev[i]],a[i]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g,flag?(P-1)/i:P-1-(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k]%P;
                ll t=a[j+k+(i>>1)]*w%P;
                a[j+k]=(u+t)%P;
                a[j+k+(i>>1)]=(u-t+P)%P;
                w=w*wn%P;
            }
        }
    }
}
void NTT(int len,ll *a,ll *b,ll *res)  //len=2^k
{
    int lg2=0,tlen=len,inv=ksm(len,P-2);
    while(tlen) lg2++,tlen>>=1;
    lg2--;
    for(int i=0;i<len;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    _NTT(a,len,1);_NTT(b,len,1);
    for(int i=0;i<len;i++) res[i]=a[i]*b[i]%P;
    _NTT(res,len,0);
    for(int i=0;i<len;i++) (res[i]*=inv)%=P;
}
void solve(int L,int R)
{
    if(L==R)
    {
        dp[L]=(w[L]-1ll*dp[L]*fac[L-1]%P+P)%P;
        return;
    }
    int mid=(L+R)>>1,tot=1,lel=R-L+1;
    solve(L,mid);while(tot<=lel) tot<<=1;
    for(int i=0;i<R-L;i++) tp2[i]=w[i+1]*ifac[i+1]%P;
    for(int i=R-L;i<=tot;i++) tp2[i]=0;
    for(int i=0;i<mid-L+1;i++) tp1[i]=dp[i+L]*ifac[i+L-1]%P;
    for(int i=mid-L+1;i<=tot;i++) tp1[i]=0;
    for(int i=0;i<=tot;i++) tp3[i]=0;
    NTT(tot,tp1,tp2,tp3);
    for(int i=mid+1;i<=R;i++)  (dp[i]+=tp3[i-L-1])%=P;
    solve(mid+1,R);
}
int n;
int main()
{
    scanf("%d",&n);
    fac[0]=1;ifac[0]=1;
    w[0]=2;
    for(int i=1;i<=n;i++) w[i]=ksm(2,1ll*i*(i-1)/2);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
    ifac[n]=ksm(fac[n],P-2);
    for(int i=n-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%P;
    solve(1,n);
    // for(int i=1;i<=n;i++) printf("%lld ",dp[i]);
    // puts("");
    printf("%lld\n",dp[n]);
}
