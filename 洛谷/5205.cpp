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

const int MAXN=262145<<2;
const int P=998244353;
const int g[2]={3,332748118};
const int inv2=(P+1)>>1;

namespace FastIO{
    inline char get_char()
    {
        static char buf[1000001],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
    }

    template<typename T>
        inline void read(T& x)
        {
            x=0;static char ch=get_char();
            while(!isdigit(ch)) ch=get_char();
            while(isdigit(ch)) x=x*10+(ch^'0'),ch=get_char();
        }

    #if __cplusplus >= 201103L
        template<typename T,typename ...Args>
            inline void read(T& x,Args& ...args)
            {
                read(x);
                read(args...);
            }
    #endif
}

using namespace FastIO;

int rev[MAXN],n,m;
ll h[MAXN],f[MAXN];

ll inc(ll x,ll y){x+=y;return x>P?x-P:x;}

ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

namespace Poly_mul{ll t1[MAXN],t2[MAXN],t3[MAXN],t4[MAXN];}
namespace Poly_inv{ll t1[MAXN],t2[MAXN];}
namespace Poly_sqrt{ll t1[MAXN],t2[MAXN];}

void clear(ll *a,int n)
{
    int t=1;
    while(t<n) t<<=1;
    memset(a+t,0,sizeof(ll)*(t-n));
}

void clear_all(ll *a,int n)
{
    int t=1;
    while(t<n) t<<=1;
    memset(a,0,sizeof(ll)*t);
}

void NTT(ll *a,int n,int f)
{
    for(int i=0;i<n;i++)
        if(i>rev[i])	swap(a[i],a[rev[i]]);
    for(int	i=2;i<=n;i<<=1)
    {
        ll wn=ksm(g[f],(P-1)/i);
        for(int j=0;j<n;j+=i)
        {
            ll w=1;
            for(int k=0;k<(i>>1);k++)
            {
                ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
                a[j+k]=inc(u,t);a[j+k+(i>>1)]=dec(u,t);
                w=w*wn%P;
            }
        }
    }
}

void multiply(ll *a,ll *b,ll *Res,int n)
{
    using namespace Poly_mul;
    int tot=1,lg2=0;
    while(tot<(n<<1)) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
    for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
    NTT(t1,tot,0);NTT(t2,tot,0);
    for(int i=0;i<tot;i++) t4[i]=t1[i]*t2[i]%P;
    NTT(t4,tot,1);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++) Res[i]=t4[i]*inv%P;
}

void multiply(ll *a,ll *b,ll *c,ll *Res,int n)
{
    using namespace Poly_mul;
    int tot=1,lg2=0;
    while(tot<(n<<1)) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
    memset(t3,0,sizeof(ll)*tot);
    for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i],t3[i]=c[i];
    NTT(t1,tot,0);NTT(t2,tot,0);NTT(t3,tot,0);
    for(int i=0;i<tot;i++) t4[i]=t1[i]*t2[i]%P*t3[i]%P;
    NTT(t4,tot,1);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++) Res[i]=t4[i]*inv%P;
}

void poly_inverse(ll *a,ll *Res,int n)
{
    using namespace Poly_inv;
    clear_all(Res,n);clear_all(t1,n);clear_all(t2,n);
    int l=1;Res[0]=ksm(a[0],P-2);
    while(l<n)
    {
        for(int i=0;i<l;i++) t2[i]=2*Res[i]%P;
        l<<=1;
        multiply(Res,Res,a,t1,l);
        for(int i=0;i<l;i++) Res[i]=dec(t2[i],t1[i]);
    }
}

void poly_sqrt(ll *a,ll *Res,int n)
{
    using namespace Poly_sqrt;
    int l=1;Res[0]=1;
    while(l<(n<<1))
    {
        multiply(Res,Res,t1,l);poly_inverse(Res,t2,l);
        l<<=1;
        for(int i=0;i<l;i++) t1[i]=inc(t1[i],a[i])*inv2%P;
        multiply(t1,t2,Res,l);
    }
}

int main()
{
    read(n);
    for(int i=0;i<n;i++) read(f[i]);
    poly_sqrt(f,h,n);
    for(int i=0;i<n;i++) printf("%lld%c",h[i],"\n "[i!=n-1]);
}