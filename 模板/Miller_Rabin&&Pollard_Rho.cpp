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
typedef unsigned __int128 uint128;
using namespace std;

const int base[]={2,3,7,61,24251};

ll ans;

inline ll ksm(ll a,ll b,const ll &P)
{
    ll ret=1;
    for(;b;(a*=a)%=P,b>>=1) if(b&1) (ret*=a)%=P;
    return ret;
}
ll gcd(ll a,ll b)
{
    if(!a||!b) return a|b;
    if(a<b) return gcd(b%a,a);
    else return gcd(a%b,b);
}

inline bool Miller_Rabin(ll x)
{
    if(x<2||x==46856248255981ll) return false;
    if(x==2||x==3||x==7||x==61||x==24251) return true;
    ll t=x-1,r;int tms=0,j;
    while(!(t&1)) ++tms,t>>=1;
    for(int i=0;i<5;i++)
    {
        r=ksm(base[i],t,x);
        if(r==1||r==x-1) continue;
        for(j=1;j<=tms;j++)
        {
            r=(uint128)r*r%x;
            if(r==x-1) break;
        }
        if(j>tms) return false;
    }
    return true;
}

inline ll Pollard_Rho(ll x,int c)
{
    ll t1,t2,d;
    int cnt=1,lim=2;
    t1=t2=(uint128)rand()*rand()*rand()*rand()%(x-1)+1;
    while(true)
    {
        ++cnt;
        t1=((uint128)t1*t1%x+c)%x;
        d=gcd(x,abs(t2-t1));
        if(d>1&&d<x) return d;
        if(t1==t2) return x;
        if(cnt==lim) cnt=0,lim<<=1,t2=t1;
    }
}

inline void factor(ll x,int cnt)
{
    if(x==1||x<=ans) return;
    if(Miller_Rabin(x)) return ans=max(ans,x),void();
    ll t=x;
    while(t==x) t=Pollard_Rho(t,cnt--);
    while(x%t==0) x/=t;
    factor(x,cnt);factor(t,cnt);
}

void solve()
{
    ans=0;ll x;
    scanf("%lld",&x);
    factor(x,23333333);
    if(ans==x) puts("Prime");
    else printf("%lld\n",ans);
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}