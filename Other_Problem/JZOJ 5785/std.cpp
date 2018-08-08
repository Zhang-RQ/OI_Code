#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int P=998244353;
const int g[2]={3,332748118};
const int MAXN=65537;

int rev[MAXN],n,k;
ll t1[MAXN],t2[MAXN],F[MAXN];

ll ksm(ll a,ll b)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

inline ll inc(ll a,const ll &b) {a+=b;return a>P?a-P:a;}
inline ll dec(ll a,const ll &b) {a-=b;return a<0?a+P:a;}

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
                w=w*wn%P;
            }
        }
    }
}

void multiply(ll *a,ll *b,ll *res,int n) //0..n-1
{
    int tot=1,lg2=0;
    while(tot<(n<<1)) tot<<=1,lg2++;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
    memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
    for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
    NTT(t1,tot,0);NTT(t2,tot,0);
    for(int i=0;i<tot;i++)
        t1[i]=t1[i]*t2[i]%P;
    NTT(t1,tot,1);
    ll inv=ksm(tot,P-2);
    for(int i=0;i<tot;i++)
        res[i]=t1[i]*inv%P;
}

void prework(ll *f,ll *res,int k,int l) //F(x) =>F(2^k*x) //0..l-1
{
    memset(res,0,sizeof t1);
    for(int i=0;i<l;i++)
        res[i]=ksm(2,i*k)*f[i]%P;
}

void solve(ll *res,int p) // Get F_p(x)
{
    static ll t[MAXN],t1[MAXN];
    int now=0,pw2=1;
    memset(t,0,sizeof t);
    ll C=k,fac=1;
    for(int i=1;i<=k;i++) (fac*=i)%=P,t[i]=ksm(fac,P-2),C=C*(k-i)%P*ksm(i+1,P-2)%P;
    res[0]=1;
    while(p)
    {
        if(p&1) prework(t,t1,now,k+1),multiply(res,t1,res,k+1),now|=pw2;
        prework(t,t1,pw2,k+1),multiply(t,t1,t,k+1);
        p>>=1,pw2<<=1;
    }
}

int main()
{
    freopen("or.in","r",stdin);
    freopen("or.out","w",stdout);
    scanf("%d%d",&n,&k);
    solve(F,n);
    ll ans=0,fac=1,C=k;
    for(int i=1;i<=k;i++)
        (fac*=i)%=P,(ans+=F[i]*C%P*fac%P)%=P,C=C*(k-i)%P*ksm(i+1,P-2)%P;
    printf("%lld\n",ans);
}
