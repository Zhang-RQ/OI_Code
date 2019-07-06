#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const ll INFll=1ll<<60;

ll Li,Ri,p,q;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
        return x=1,y=0,void();
    exgcd(b,a%b,y,x);
    y-=(a/b)*x;
}

ll sub_f(ll a,ll b,ll c,ll n)
{
    if(n<=0) return 0;
    return n*(n-1)/2*(a/c)+n*(b/c)+sub_f(c,(a*n+b)%c,a%c,(a%c*n+b%c)/c);
}

ll calc(ll a, ll b, ll c, ll n)
{
    if(c<0)
    {
        c=-c;
        a=-a,b=-b;
        return calc(a,b,c,n);
    }
    if(a<0)
    {
        a=-a;
        return calc(a,b-a*(n-1),c,n);
    }
    if(b<0)
    {
        b=-b;
        ll k=b/c+(b%c!=0);
        return calc(a,k*c-b,c,n)-k*n;
    }
    return sub_f(a,b,c,n);
}

bool Chk(ll M)
{
    ll sec1=calc(2*p,-q+M,2*q,Ri+1)-calc(2*p,-q+M,2*q,Li);
    ll sec2=calc(2*p,-q-M-1,2*q,Ri+1)-calc(2*p,-q-M-1,2*q,Li);
    return sec1-sec2>0;
}

ll solve(ll a,ll b,ll m)//ax=b (mod m)
{
    b=(b%m+m)%m;a=(a%m+m)%m;
    ll d=gcd(a,m);
    if(b%d)
        return INFll;
    ll x,y,Mod=m/d;
    exgcd(a/d,Mod,x,y);
    x=(x%Mod+Mod)%Mod;
    ll tmp=x*(b/d)%Mod;
    ll final_ans=Li+((tmp%Mod)-(Li%Mod)+Mod)%Mod;
    return final_ans;
}

void solve()
{
    scanf("%lld%lld%lld%lld",&Li,&Ri,&p,&q);
    ll d=gcd(p,q);
    p/=d,q/=d;
    ll L=0,R=q,M=q;
    while(L<=R)
    {
        ll Mid=(L+R)>>1;
        if(Chk(Mid))
            M=Mid,R=Mid-1;
        else
            L=Mid+1;
    }
    printf("%lld\n",min(solve(2*p,q-M,2*q),solve(2*p,q+M,2*q)));
}

int main()
{
    int t;
    for(scanf("%d",&t);t--;solve());
}
