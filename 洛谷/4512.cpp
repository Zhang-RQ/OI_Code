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

#define DEBUG_E printf("Passing Line %d in Function \"%s\"(Enter)\n",__LINE__,__FUNCTION__)
#define DEBUG_O printf("Passing Line %d in Function \"%s\"(Exit)\n",__LINE__,__FUNCTION__)

const int MAXN=262145;
const int P=998244353;
const int g=3;

int n,m;
ll F[MAXN],G[MAXN],Q[MAXN],R[MAXN];

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
    void multiply(ll *a,ll *b,ll *res,int n)
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

namespace Poly_division{
    ll t1[MAXN],t2[MAXN];
    void division(ll *F,ll *G,ll *H,ll *R,int n,int m) //F=G*H+R F=..x^n,G=..x^m 
    {
        reverse(F,F+n+1);reverse(G,G+m+1);
        Poly_inverse::inverse(G,t1,n-m+1);
        NTT::multiply(F,t1,H,n);
        reverse(H,H+n-m+1);
        for(int i=n-m+1;i<=n;i++) H[i]=0;
        reverse(G,G+m+1);reverse(F,F+n+1);
        NTT::multiply(H,G,t2,max(n-m,m)+1);
        for(int i=0;i<m;i++) R[i]=(F[i]-t2[i]+P)%P;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++) scanf("%lld",&F[i]);
    for(int i=0;i<=m;i++) scanf("%lld",&G[i]);
    Poly_division::division(F,G,Q,R,n,m);
    for(int i=0;i<=n-m;i++) printf("%lld%c",Q[i],i==n-m?'\n':' ');
    for(int i=0;i<m;i++) printf("%lld%c",R[i],i==m-1?'\n':' ');
    #ifdef LOCAL
        system("pause");
    #endif
}