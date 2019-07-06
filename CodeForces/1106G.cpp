#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int pr[]={2,3,5,7,11,23,43,79};
const int M=(1<<8)-1;

const int MAXN=2E5+10;

int n,f[1<<16];
ll a[MAXN],X,Y;
map<ll,ll> M_pr,ID;

mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
ll RandInt(ll L,ll R){return uniform_int_distribution<ll>(L,R)(RandEngine);}

ll Mx=0;

ll gcd(ll a,ll b)
{
    if(!a||!b) return a|b;
    #define ctz __builtin_ctzll
    int shift=ctz(a|b);
    b>>=shift;
    while(a)
    {
        a>>=ctz(a);
        if(a<b)
            swap(a,b);
        a-=b;
    }
    return b<<shift;
    #undef ctz
}

ull Mul(ull a,ull b,ull P)
{
    //return (__int128)a*b%P;
    ull c=(ll)a*b-(ll)((ull)((long double)a*b/P))*P;
    return (c+P)%P;
}

ll ksm(ll a,ll b,ll P)
{
    ll ret=1;
    for(;b;b>>=1,a=Mul(a,a,P))
        if(b&1)
            ret=Mul(ret,a,P);
    return ret;
}

bool Miller_Rabin(ll n)
{
    if(n==2||n==3||n==5||n==7||n==11||n==23||n==43||n==79)
        return true;
    if(~n&1)
        return false;
    for(int p:pr)
    {
        ll t=n-1,c=0;
        while(~t&1)
            t>>=1,++c;
        ll pw=ksm(p,t,n);
        if(pw==1)
            continue;
        bool f=(pw==n-1);
        while(c)
        {
            pw=Mul(pw,pw,n);
            f|=(pw==n-1);
            --c;
            if(pw==1&&!f)
                return false;
        }
        if(pw!=1||!f)
            return false;
    }
    return true;
}

ll Pollard_Rho(ll n)
{
    int c=RandInt(1,n-1);
    ll t=1,x=0,y=0,q=1;
    auto F=[=](ll x){return (Mul(x,x,n)+c)%n;};
    for(int i=2;;i<<=1,y=x,q=1)
    {
        for(int j=1;j<=i;j++)
        {
            x=F(x);
            q=Mul(q,abs(x-y),n);
            if(!(j&M))
            {
                if((t=gcd(q,n))>1)
                   break;
            }
        }
        if(t>1||((t=gcd(q,n))>1))
            break;
    }
    if(t==n)
    {
        t=1;
        while(t==1)
            x=F(x),t=gcd(abs(x-y),n);
    }
    return t;
}

void Factorize(ll n)
{
    if(n==1)
        return;
    if(Miller_Rabin(n))
        return ++M_pr[n],void();
    ll d=n;
    while(d==n)
        d=Pollard_Rho(n);
    Factorize(n/d);Factorize(d);
}

int main()
{
    scanf("%d%lld%lld",&n,&X,&Y);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    if(Y%X)
        return puts("0"),0;
    Factorize(Y);
    map<ll,ll> Pr_Y=M_pr;
    M_pr.clear();
    Factorize(X);
    map<ll,ll> Pr_X=M_pr;
    int tot=Pr_Y.size(),ful=(1<<tot)-1,tmp=0,ofs=0;
    for(auto Pr:Pr_Y)
        ID[Pr.first]=tmp++;
    for(int i=1;i<=n;i++)
        if(!(a[i]%X))//i
        {
            int s=0;ll x=a[i];
            for(auto Pr:Pr_Y)
            {
                int tms=0;
                while(!(x%Pr.first))
                    x/=Pr.first,++tms;
                if(tms&&!Pr_X.count(Pr.first))
                    s|=1<<ID[Pr.first];
                else if(Pr_X.count(Pr.first))
                    s|=(tms!=Pr_X[Pr.first])<<ID[Pr.first];
            }
            f[s]++;
        }
    for(auto Pr:Pr_X)
        ofs|=(Pr.second==Pr_Y[Pr.first])<<ID[Pr.first];
    ll Ans=0;
    for(int i=0;i<tot;i++)
        for(int s=0;s<1<<tot;s++)
            if((s>>i)&1)
                f[s]+=f[s^(1<<i)];
    for(int i=1;i<=n;i++)
        if(!(Y%a[i]))//j
        {
            int s=0;
            for(auto Pr:Pr_Y)
            {
                int tms=0;ll x=a[i];
                while(!(x%Pr.first))
                    x/=Pr.first,++tms;
                s|=(tms!=Pr.second)<<ID[Pr.first];
            }
            s=(s|ofs)^ofs;
            Ans+=f[ful^s];
        }
    printf("%lld\n",Ans);
}
