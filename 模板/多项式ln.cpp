// luogu-judger-enable-o2
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int P=998244353;
const int g[]={3,332748118};
const int MAXN=262145<<1;

int rev[MAXN];

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

__attribute__((always_inline)) ll inc(ll a,const ll &b){a+=b;return a>P?a-P:a;}
__attribute__((always_inline)) ll dec(ll a,const ll &b){a-=b;return a<0?a+P:a;}

namespace NTT{
    ll t1[MAXN],t2[MAXN];
    void NTT(ll *a,int n,bool f)
    {
        for(int i=0;i<n;i++)
            if(rev[i]>i) swap(a[i],a[rev[i]]);
        for(int i=2;i<=n;i<<=1)
        {
            ll wn=ksm(g[f],(P-1)/i);
            for(int j=0;j<n;j+=i)
            {
                ll w=1;
                for(int k=0;k<(i>>1);k++)
                {
                    ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
                    a[j+k]=inc(u,t);a[j+k+(i>>1)]=dec(u,t);
                    (w*=wn)%=P;
                }
            }
        }
    }
    void multiply(ll *a,ll *b,ll *res,int n)
    {
        int tot=1,lg2=0;
        while((n<<1)>tot) tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
        for(int i=0;i<n;i++)
            t1[i]=a[i],t2[i]=b[i];
        NTT(t1,tot,0);NTT(t2,tot,0);
        for(int i=0;i<tot;i++) t1[i]=t1[i]*t2[i]%P;
        NTT(t1,tot,1);
        ll inv=ksm(tot,P-2);
        for(int i=0;i<tot;i++) res[i]=t1[i]*inv%P;
    }
}

namespace Poly_inverse{
    ll t1[MAXN],t2[MAXN];
    void inverse(ll *f,ll *res,int n)
    {
        int l=1; //mod x^l
        memset(res,0,sizeof t1);
        res[0]=ksm(f[0],P-2);
        while(l<n)
        {
            for(int i=0;i<l;i++) t1[i]=2*res[i]%P;
            NTT::multiply(res,res,res,l);
            NTT::multiply(res,f,res,l<<1);
            l<<=1;
            for(int i=0;i<l;i++) res[i]=(t1[i]-res[i]+P)%P;
        }
    }
}

void derivation(ll *f,int n)
{
    for(int i=0;i<n-1;i++) f[i]=f[i+1]*(i+1)%P;
    f[n-1]=0;
}

void integral(ll *f,int n)
{
    for(int i=n-1;~i;i--) f[i]=f[i-1]*ksm(i,P-2)%P;
    f[0]=0;
}

ll f[MAXN],b[MAXN],c[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld",&f[i]);
    Poly_inverse::inverse(f,b,n);
    derivation(f,n);
    NTT::multiply(f,b,c,n); 
    integral(c,n);
    for(int i=0;i<n;i++) printf("%lld%c",c[i],i==n-1?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}
