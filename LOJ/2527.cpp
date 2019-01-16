#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1004535809;
const int g[]={3,(P+1)/3};
const int MAXN=1E7+10;
const int MAXM=262145<<1;

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

namespace Poly_Mul{ll t1[MAXM],t2[MAXM],t3[MAXM];}

int rev[MAXM],w[MAXM],n,m,s,lim,mx;
ll fac[MAXN],ifac[MAXN],F[MAXM],G[MAXM],H[MAXM];

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}

ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

void NTT(ll *a,int n,int f)
{
    for(int i=0;i<n;i++)
        if(i>rev[i])
            swap(a[i],a[rev[i]]);
    for(int i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g[f],(P-1)/i);
        for(ll *x=a,*y=a+(i>>1),*ed=a+n;x!=ed;x+=i,y+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=x[k],t=y[k]*w%P;
                x[k]=inc(u,t);y[k]=dec(u,t);
                w=w*wn%P;
            }
        }
    }
}

void Mul(ll *a,ll *b,ll *Res,int n,int m)
{
    using namespace Poly_Mul;
    int tot=1,lg2=0;
    while(tot<n+m) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
    for(int i=0;i<n;i++) t1[i]=a[i];
    for(int i=0;i<m;i++) t2[i]=b[i];
    NTT(t1,tot,0);NTT(t2,tot,0);
    for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
    NTT(t3,tot,1);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<n+m-1;i++) Res[i]=t3[i]*inv%P;
}

int main()
{
    scanf("%d%d%d",&n,&m,&s);lim=min(m,n/s);mx=max(n,m);
    for(int i=0;i<=m;i++) scanf("%d",&w[i]);
    fac[0]=ifac[0]=1;
    for(int i=1;i<=mx;i++) fac[i]=fac[i-1]*i%P;
    ifac[mx]=ksm(fac[mx],P-2);
    for(int i=mx-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
    for(int i=0;i<=lim;i++) F[i]=fac[n]*fac[m]%P*ifac[i]%P*ifac[m-i]%P*ifac[n-s*i]%P*ksm(ifac[s],i)%P*ksm(m-i,n-s*i)%P;
    for(int i=0;i<=lim;i++) F[i]=F[i]*fac[i]%P;
    for(int i=0;i<=lim;i++) G[i]=i&1?dec(0,ifac[i]):ifac[i];
    reverse(F,F+1+lim);
    Mul(F,G,H,lim+1,lim+1);
    reverse(H,H+1+lim);
    for(int i=0;i<=lim;i++) H[i]=H[i]*ifac[i]%P;
    ll Ans=0;
    for(int i=0;i<=lim;i++) Ans=inc(Ans,w[i]*H[i]%P);
    printf("%lld\n",Ans);
}