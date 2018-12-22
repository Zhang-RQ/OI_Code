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

const int MAXN=262145;

template<int P,int g>
    class base_NTT_solver{
        private:
        int rev[MAXN];
        ll t1[MAXN],t2[MAXN],t3[MAXN];
        
        inline ll inc(ll x,ll y){x+=y;return x>P?x-P:x;}

        inline ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

        ll ksm(ll a,ll b)
        {
            ll ret=1;
            for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
            return ret;
        }

        void NTT(ll *a,int n,int f)
        {
            for(int i=0;i<n;i++)
                if(rev[i]>i)
                    swap(a[i],a[rev[i]]);
            for(int i=2;i<=n;i<<=1)
            {
                ll wn=ksm(g,f?(P-1)/i:(P-1-(P-1)/i));
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

        public:
        void multiply(ll *a,ll *b,ll *Res,int n)
        {
            int lg2=0,tot=1;
            while((n<<1)>tot) tot<<=1,lg2++;
            for(int i=0;i<tot;i++)
                rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
            memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
            for(int i=0;i<n;i++)
                t1[i]=a[i],t2[i]=b[i];
            NTT(t1,tot,1);NTT(t2,tot,1);
            for(int i=0;i<tot;i++) 
                t3[i]=t1[i]*t2[i]%P;
            NTT(t3,tot,0);
            ll inv=ksm(tot,P-2);
            for(int i=0;i<tot;i++)
                Res[i]=t3[i]*inv%P;
        }
    };


class NTT_solver{
    public: ll P;
    private:
    ll t1[MAXN],t2[MAXN],t3[MAXN];
    base_NTT_solver<998244353,3> N1;
    base_NTT_solver<469762049,3> N2;
    base_NTT_solver<167772161,3> N3;

    const ll P1=998244353,P2=469762049,P3=167772161;
    const ll LL_MAX=9223372036854775807ll,M=P1*P2;

    inline ll mul(ll a,ll b,ll mod)
    {
        a=(a%mod+mod)%mod;b=(b%mod+mod)%mod;
        if(a+1<LL_MAX/b) return a*b%mod;
        ll ret=0;
        for(;b;b>>=1,a=(a+a)%mod) if(b&1) ret=(ret+a)%mod;
        return ret;
    }

    inline ll ksm(ll a,ll b,ll mod)
    {
        ll ret=1;a%=mod;
        for(;b;b>>=1,a=a*a%mod) if(b&1) ret=ret*a%mod;
        return ret;
    }

    public:
    void multiply(ll *a,ll *b,ll *Res,int n)
    {
        N1.multiply(a,b,t1,n);N2.multiply(a,b,t2,n);N3.multiply(a,b,t3,n);
        int len=2*n;
        for(int i=0;i<len;i++)
        {
            ll t=(mul(t1[i]*P2%M,ksm(P2,P1-2,P1),M)+mul(t2[i]*P1%M,ksm(P1,P2-2,P2),M))%M;
            Res[i]=((((t3[i]-t)%P3+P3)%P3*ksm(M,P3-2,P3)%P3)*(M%P)%P+t)%P;
        }
    }
}N;

int n,m,P;
ll a[MAXN],b[MAXN],Res[MAXN];

int main()
{
    scanf("%d%d%d",&n,&m,&P);N.P=P;
    for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<=m;i++) scanf("%lld",&b[i]);
    N.multiply(a,b,Res,max(n+1,m+1));
    for(int i=0;i<=n+m;i++) printf("%lld%c",Res[i],"\n "[i!=n+m]);
}