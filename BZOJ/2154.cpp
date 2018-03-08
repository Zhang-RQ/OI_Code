#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXP=1E7+10;
const int P=20101009;
int prime[MAXP],siz;
ll h[MAXP];
bool vis[MAXP];
ll sum[MAXP];
void get()
{
    h[1]=1;
    for(int i=2;i<MAXP-5;i++)
    {
        if(!vis[i])  {prime[++siz]=i;h[i]=i*(1ll-i)%P;}
        for(int j=1;j<=siz&&prime[j]*i<MAXP-5;j++)
        {
            vis[prime[j]*i]=1;
            if(!(i%prime[j]))
                {h[i*prime[j]]=h[i]*prime[j]%P;break;}
            else h[i*prime[j]]=h[i]*h[prime[j]]%P;
        }
    }
    for(int i=1;i<MAXP-5;i++)
        sum[i]=(sum[i-1]+h[i])%P;
}
ll Sum(ll x,ll y)
{
    x%=P;y%=P;
    ll re1=(x*(x+1)>>1)%P;
    ll re2=(y*(y+1)>>1)%P;
    return (re1*re2)%P;
}
ll solve(ll n,ll m)
{
    if(n>m) swap(n,m);
    int lim=min(n,m);
    ll ans=0;
    for(int d=1;d<=lim;)
    {
        int pos=min(n/(n/d),m/(m/d));
        (ans+=(sum[pos]-sum[d-1])*Sum(n/d,m/d)%P)%=P;
        d=pos+1;
    }
    return (ans+P)%P;
}
ll T,M,N;
int main()
{
    get();
    scanf("%lld%lld",&N,&M);
    printf("%lld\n",solve(N,M)%P);
}
