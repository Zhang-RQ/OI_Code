// luogu-judger-enable-o2
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
const int MAXN=262145;

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

namespace NTT{
    int rev[MAXN];
    ll t1[MAXN],t2[MAXN],t3[MAXN];
    inline void NTT(ll *a,int n,bool f) //n=2^k
    {
        for(int i=0;i<n;i++)
            if(rev[i]>i) swap(a[i],a[rev[i]]);
        for(int i=2;i<=n;i<<=1)
        {
            ll wn=ksm(g,f?(P-1)/i:P-1-(P-1)/i);
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
    inline void multiply(ll *a,ll *b,ll *res,int n) //n!=2^k 0--n-1
    {
        int tot=1,lg2=0;
        while(tot<n<<1) tot<<=1,lg2++;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
        memset(t1,0,tot*sizeof(ll));memset(t2,0,tot*sizeof(ll));
        for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
        NTT(t1,tot,1);NTT(t2,tot,1);
        for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
        NTT(t3,tot,0);
        ll inv=ksm(tot,P-2);
        for(int i=0;i<tot;i++) res[i]=t3[i]*inv%P;
    }
}

namespace Ploy_inverse{
    ll t1[MAXN],t2[MAXN];
    void inverse(ll *a,ll *res,int n)
    {
        int l=1; // mod x^l
        res[0]=ksm(a[0],P-2);
        while(l<=n)
        {
            memcpy(t1,res,l*sizeof(ll));
            NTT::multiply(t1,t1,res,l);
            NTT::multiply(res,a,t2,l<<1);
            for(int i=0;i<l<<1;i++)  res[i]=(2*t1[i]%P-t2[i]+P)%P;
            l<<=1;
        }
    }
}
int n;ll a[MAXN],res[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    Ploy_inverse::inverse(a,res,n);
    for(int i=0;i<n;i++) printf("%lld%c",res[i],i==n-1?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}