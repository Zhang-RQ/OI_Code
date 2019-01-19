#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int bs[]={2,3,5,7,11,17,23,29};
const int M=(1<<7)-1;

ll Mx;

ll Mul(ll a,ll b,ll P){return ((a*b)-(ll)((long double)a*b/P)*P+P)%P;}

// ll Mul(ll a,ll b,ll P){return (__int128_t)a*b%P;}

ll gcd(ll a, ll b) {
    if (!a) return b;
    if (!b) return a;
#define ctz __builtin_ctzll
    int t = ctz(a | b);
    a >>= ctz(a);
    do {
        b >>= ctz(b);
        if (a > b) {
            ll t = b;
            b = a;
            a = t;
        }
        b -= a;
    } while (b != 0);
    return a << t;
}

ll ksm(ll a,ll b,ll P)
{
    ll ret=1;
    for(;b;b>>=1,a=Mul(a,a,P)) if(b&1) ret=Mul(ret,a,P);
    return ret;
}

bool Miller_Rabin(ll x)
{
    if(x==2||x==3||x==5||x==7||x==11||x==17||x==23||x==29) return true;
    for(int p:bs)
    {
        ll b=x-1;int t=0,f=0;
        while(~b&1) b>>=1,t++;
        if(!t) return false;
        ll a=ksm(p,b,x);
        if(a==1||a==x-1) {continue;}
        while(t)
        {
            a=Mul(a,a,x);f|=(a==x-1);
            if(a==1&&!f) return false;
            t--;
        }
        if(a!=1||!f) return false;
    }
    return true;
}

ll f(ll x,ll n,ll c){return (Mul(x,x,n)+c)%n;}

ll Pollard_Rho(ll n) // find 
{
    ll x=0,y=x,q=1,t=1,c=rand()%(n-1)+1;
    for(int k=2;;k<<=1,y=x,q=1)
    {
        for(int i=1;i<=k;i++)
        {
            x=f(x,n,c);
            q=Mul(q,abs(x-y),n);
            if(!(M&i))
            {
                t=gcd(q,n);
                if(t>1) break;
            }
        }
        if(t>1||(t=gcd(q,n))>1) break;
    }
    if(t==n)
    {
        t=1;
        while(t==1) t=gcd(abs((x=f(x,n,c))-y),n);
    }
    return t;
}

void Factorize(ll n)
{
    if(n==1) return;
    if(Miller_Rabin(n)) return Mx=max(Mx,n),void();
    ll t=Pollard_Rho(n);
    while(t==n) t=Pollard_Rho(n);
    Factorize(t);Factorize(n/t);
}

int main()
{
    srand((ull)new char);
    int T;ll n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        if(Miller_Rabin(n)) {puts("Prime");continue;}
        Mx=0;Factorize(n);
        printf("%lld\n",Mx);
    }
}