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
const int P=1000000007;
const int siz=5000000;
const int rev2=500000004;
bool vis[siz+5];
int prime[siz+1],vnum,phi[siz+5],sum[siz+5];
map<ll,int> mp;
void init()
{
    phi[1]=sum[1]=1;
    for(int i=2;i<=siz;i++)
    {
        if(!vis[i])
        {
            prime[++vnum]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=vnum&&prime[j]*i<=siz;j++)
        {
            vis[prime[j]*i]=1;
            if(!(i%prime[j]))
            {
                phi[prime[j]*i]=phi[i]*prime[j];
                break;
            }
            else phi[prime[j]*i]=phi[i]*phi[prime[j]];
        }
    }
    for(int i=1;i<=siz;i++)
        (sum[i]=sum[i-1]+phi[i])%=P;
}
ll ask(ll x)
{
    if(x<=siz) return sum[x];
    if(mp.count(x)) return mp[x];
    ll ret;
    if(x%P!=0) ret=(x%P)*((x%P)+1)%P*rev2%P;
    else ret=0;
    ll xx;
    for(ll i=2;i<=x;i=xx+1)
    {
        xx=x/(x/i);
        ret-=ask(x/i)*(xx-i+1);
        ret%=P;
    }
    (ret+=P)%=P;
    mp[x]=ret;
    return ret;
}
int main()
{
    init();
    ll n;
    scanf("%lld",&n);
    printf("%lld\n",ask(n));
}
