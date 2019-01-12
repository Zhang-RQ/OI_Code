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

ll inc(ll a,const ll &b){a+=b;return a>P?a-P:a;}
ll dec(ll a,const ll &b){a-=b;return a<0?a+P:a;}

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

int n;
ll a[MAXN],b[MAXN],fac[MAXN],ifac[MAXN],h[MAXN],f[MAXN],t[MAXN];

int main()
{
	scanf("%d",&n);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
	ifac[n]=ksm(fac[n],P-2);
	for(int i=n-1;i;i--)  ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++) h[i]=ksm(2,1ll*i*(i-1)/2)*ifac[i]%P;
	h[0]++;
	Poly_inverse::inverse(h,f,n+1);
	h[0]--;
	NTT::multiply(f,h,t,n+1);
	for(int i=1;i<=n;i++) t[i]=t[i]*fac[i]%P;
	puts("1");
	for(int i=2;i<=n;i++) printf("%lld\n",t[i]?fac[i]*ksm(2,1ll*i*(i-1)/2-i)%P*ksm(1ll*i*t[i]%P,P-2)%P:-1);
}