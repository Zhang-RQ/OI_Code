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
const int g=3;
const int MAXN=262145<<1;

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

inline ll inc(ll a,ll b){a+=b;return a>P?a-P:a;}
inline ll dec(ll a,ll b){a-=b;return a<0?a+P:a;}

namespace NTT{
    int rev[MAXN];
    ll t1[MAXN],t2[MAXN],t3[MAXN];
    inline void NTT(ll *a,int n,int f)
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
                    ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
                    a[j+k]=inc(u,t);a[j+k+(i>>1)]=dec(u,t);
                    (w*=wn)%=P;
                }
            }
        }
    }
    inline void multiply(ll *a,ll *b,ll *res,int n)
    {
        int tot=1,lg2=0;
        while(tot<(n<<1)) tot<<=1,lg2++;
        memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        for(int i=0;i<n;i++) t1[i]=a[i];
        for(int i=0;i<n;i++) t2[i]=b[i];
        NTT(t1,tot,1);NTT(t2,tot,1);
        for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
        NTT(t3,tot,0);
        ll inv=ksm(tot,P-2);
        for(int i=0;i<tot;i++) res[i]=t3[i]*inv%P;
    }
}

namespace Poly_inverse{
    ll t1[MAXN],t2[MAXN];
    void inverse(ll *a,ll *res,int n)
    {
        int l=1; //mod 2^l
        memset(res,0,n*sizeof(ll));
        res[0]=ksm(a[0],P-2);
        while(l<n)
        {
            memcpy(t1,res,l*sizeof(ll));
            NTT::multiply(t1,t1,res,l);
            NTT::multiply(res,a,t2,l<<1);
            for(int i=0;i<l<<1;i++)  res[i]=(2*t1[i]%P-t2[i]+P)%P;
            l<<=1;
        }
    }
}

int n;
ll G[MAXN],F[MAXN];

int main()
{
    scanf("%d",&n);
    G[0]++;
    for(int i=1;i<n;i++) scanf("%lld",&G[i]),G[i]=P-G[i];
    Poly_inverse::inverse(G,F,n);
    for(int i=0;i<n;i++) printf("%lld%c",F[i],i==n-1?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}