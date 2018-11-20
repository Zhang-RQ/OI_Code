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

const int MAXN=15;

int P,n,m,w[MAXN],sum;

ll ksm(ll a,ll b,ll p)
{
    ll ret=1;
    for(;b;b>>=1,(a*=a)%=p) if(b&1) (ret*=a)%=p;
    return ret;
}

void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b) return x=a,y=0,void();
    exgcd(b,a%b,y,x);y-=(a/b)*x;
}

ll inv(ll v,ll P)
{
    ll x,y;exgcd(v,P,x,y);
    return (x%P+P)%P;
}

pair<ll,ll> fac(ll N,ll p,ll pk,bool f)
{
    if(!N) return make_pair(1,0);
    ll ret=1,tmp=1,cnt=0;
    for(int i=1;i<pk;i++)
        if(i%p) (tmp*=i)%=pk;
    ret=ksm(tmp,N/pk,pk);
    for(int i=1;i<=N%pk;i++)
        if(i%p) (ret*=i)%=pk;
    for(int x=N;f&&x;x/=p) cnt+=x/p;
    return make_pair(ret*fac(N/p,p,pk,0).first%pk,cnt);
}

ll calc(ll p,ll pk)
{
    pair<ll,ll> Res=fac(n,p,pk,1);
    for(int i=1;i<=m;i++)
    {
        pair<ll,ll> t=fac(w[i],p,pk,1);
        (Res.first*=inv(t.first,pk))%=pk,Res.second-=t.second;
    }
    return Res.first*ksm(p,Res.second,pk)%pk;
}

pair<ll,ll> CRT(pair<ll,ll> a,pair<ll,ll> b)
{
    ll x,y,P=a.second*b.second;exgcd(a.second,b.second,x,y);
    x=(x*(b.first-a.first)%b.second+b.second)%b.second;
    return make_pair((x*a.second+a.first)%P,P);
}

int main()
{
    scanf("%d",&P);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&w[i]),sum+=w[i];
    int _P=P;w[++m]=n-sum;
    if(w[m]<0) return puts("Impossible"),0;
    pair<ll,ll> Res=make_pair(0,1);
    for(int i=2,v;1ll*i*i<=_P;i++)
        if(!(P%i))
        {
            v=1;
            while(!(P%i)) P/=i,v*=i;
            Res=CRT(Res,make_pair(calc(i,v),v));
        }
    if(P!=1) Res=CRT(Res,make_pair(calc(P,P),P));
    printf("%lld\n",Res.first);
}