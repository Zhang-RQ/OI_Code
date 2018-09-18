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
#include<ctime>
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int P=998244353;
const int g=3;
const int MAXN=262145<<2;

char B[1<<26],*S=B;

inline ll add(ll x,ll y)
{
    x+=y;
    if(x>P) x-=P;
    return x;
}

inline ll dec(ll x,ll y)
{
    x-=y;
    if(x<0) x+=P;
    return x;
}

inline ll read()
{
    ll ret=0;
    int w=1;
    char ch=*S++;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') w=-1;
        ch=*S++;
    }
    while('0'<=ch&&ch<='9')
        ret=(ret<<3)+(ret<<1),ret+=ch-'0',ch=*S++;
    return ret*w;
}

inline ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;(a*=a)%=P,b>>=1) if(b&1) (ret*=a)%=P;
    return ret;
}

int k;
ll n,a[MAXN],f[MAXN],h[MAXN],res[MAXN],base[MAXN];
ll R[MAXN],t1[MAXN],t2[MAXN],G[2][MAXN];

namespace NTT{
    int rev[MAXN];
    ll t1[MAXN],t2[MAXN],t3[MAXN],t4[MAXN];
    void NTT(ll *a,int n,bool f) // n=2^k
    {
        for(int i=0;i<n;i++)
            if(i>rev[i]) swap(a[i],a[rev[i]]);
        for(int i=2;i<=n;i<<=1)
        {
            ll wn=G[f][i];
            for(int j=0;j<n;j+=i)
            {
                ll w=1;
                for(int k=0;k<(i>>1);k++)
                {
                    ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
                    a[j+k]=add(u,t);
                    a[j+k+(i>>1)]=dec(u,t);
                    (w*=wn)%=P;
                }
            }
        }
    }
    void multiply(ll *a,ll *b,ll *res,int n) //a,b < n n!=2^k
    {
        int tot=1,lg2=0;
        while(tot<(n<<1)) tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
        for(int i=n;i<tot;i++) t1[i]=t2[i]=0;
        NTT(t1,tot,1);NTT(t2,tot,1);
        for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
        NTT(t3,tot,0);
        ll inv=ksm(tot,P-2);
        for(int i=0;i<tot;i++) res[i]=t3[i]*inv%P;
    }
    void multiply(ll *a,ll *b,ll *c,ll *res,int n)
    {
        int tot=1,lg2=0;
        while(tot<(n<<1)) tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i],t3[i]=c[i];
        for(int i=n;i<tot;i++) t1[i]=t2[i]=t3[i]=0;
        NTT(t1,tot,1);NTT(t2,tot,1);NTT(t3,tot,1);
        for(int i=0;i<tot;i++) t4[i]=t1[i]*t2[i]%P*t3[i]%P;
        NTT(t4,tot,0);
        ll inv=ksm(tot,P-2);
        for(int i=0;i<tot;i++) res[i]=t4[i]*inv%P;
    }
}

namespace Poly_inverse{
    ll t1[MAXN];
    void inverse(ll *a,ll *res,int n) //mod 2^n
    {
        int l=1;//mod x^l
        res[0]=ksm(a[0],P-2);
        while(l<n)
        {
            for(int i=0;i<l;i++) t1[i]=res[i],res[i]=2*res[i]%P;
            for(int i=l;i<(l<<1);i++) t1[i]=0;
            NTT::multiply(t1,t1,a,t1,l<<1);
            l<<=1;
            for(int i=0;i<l;i++) res[i]=(res[i]-t1[i]+P)%P;
        }
    }
}

namespace Poly_division{
    ll rF[MAXN],rG[MAXN],t1[MAXN];
    void division(ll *F,ll *G,ll *H,ll *R,int n,int m) //F=G*H+R F(n) G(m)
    {
        memset(t1,0,sizeof(ll)*n);
        for(int i=0;i<=n;i++) rF[n-i]=F[i];
        for(int i=0;i<=m;i++) rG[m-i]=G[i];
        Poly_inverse::inverse(rG,t1,n-m+1);
        NTT::multiply(rF,t1,H,n);
        reverse(H,H+n-m+1);
        for(int i=n-m+1;i<=n;i++) H[i]=0;
        NTT::multiply(G,H,t1,n);
        for(int i=0;i<=m-1;i++) R[i]=(F[i]-t1[i]+P)%P;
    }
}

void multiply(ll *a,ll *b,ll *ress)
{
    NTT::multiply(a,b,t2,k);
    Poly_division::division(t2,f,t1,R,2*k-2,k);
    for(int i=0;i<k;i++) ress[i]=R[i];
}

void ksm1(ll n)
{
    res[0]=1;base[1]=1;
    while(n)
    {
        if(n&1) multiply(res,base,res);
        multiply(base,base,base);
        n>>=1;
    }
}

int main()
{
    fread(B,1,1<<25,stdin);
    n=read();k=read();
    for(int i=2;i<MAXN;i<<=1)
        G[0][i]=ksm(g,P-1-(P-1)/i),G[1][i]=ksm(g,(P-1)/i);
    for(int i=1;i<=k;i++) a[i]=read(),a[i]=a[i]>0?a[i]:P+a[i];
    for(int i=0;i<k;i++)  h[i]=read(),h[i]=h[i]>0?h[i]:P+h[i];
    f[k]=1;
    for(int i=0;i<k;i++) f[i]=P-a[k-i];
    ksm1(n);
    ll ans=0;
    for(int i=0;i<k;i++) (ans+=res[i]*h[i]%P)%=P;
    printf("%lld\n",ans);
}