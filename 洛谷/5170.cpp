#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int inv2=(P+1)/2;
const int inv6=(P+1)/6;

struct State{
    ll f,g,h;
    State(ll _f=0,ll _g=0,ll _h=0){f=_f;g=_g;h=_h;}
};

State Solve(ll n,ll a,ll b,ll c)
{
    ll t1=a/c%P,t2=b/c%P,S1=n*(n+1)%P*inv2%P,S2=n*(n+1)%P*(2*n+1)%P*inv6%P;
    if(n==0) return State(t2,t2*t2%P,0);
    if(a==0) return State((n+1)*t2%P,(n+1)*t2%P*t2%P,(n+1)*n/2%P*t2%P);
    if(a>=c||b>=c)
    {
        State p=Solve(n,a%c,b%c,c),Ret;
        Ret.f=(t1*S1%P+t2*(n+1)%P+p.f)%P;
        Ret.g=(t1*t1%P*S2%P+(n+1)*t2%P*t2%P+p.g+t1*t2%P*2*S1%P+2*t2*p.f%P+2*t1*p.h%P)%P;
        Ret.h=(t1*S2%P+t2*S1%P+p.h)%P;
        return Ret;
    }
    ll m=(a*n+b)/c;
    State p=Solve(m-1,c,c-b-1,a),Ret;
    m%=P;
    Ret.f=(n*m%P-p.f+P)%P;
    Ret.g=(m*(m+1)%P*n%P-2*(p.h+p.f)%P-Ret.f+2*P)%P;
    Ret.h=(m*S1*2%P-p.g-p.f+2*P)%P*inv2%P;
    return Ret;
}

int main()
{
    int T,a,b,c,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&n,&a,&b,&c);
        State Res=Solve(n,a,b,c);
        printf("%lld %lld %lld\n",Res.f,Res.g,Res.h);
    }
}