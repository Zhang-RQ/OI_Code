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

const ll P=1E9+7;
const int MAXN=3E6+10;
const ll inv2=500000004;

bool vis[MAXN];
int pri[MAXN],cnt;
ll phi[MAXN];
map<ll,ll> PHI;

void sieve()
{
    phi[1]=1;
    for(int i=2;i<MAXN;i++)
    {
        if(!vis[i]) pri[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&1ll*i*pri[j]<MAXN;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];break;}
            else phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
    for(int i=1;i<MAXN;i++) (phi[i]+=phi[i-1])%=P;
}

ll ask(ll n)
{
    if(n<MAXN) return phi[n];
    if(PHI.find(n)!=PHI.end()) return PHI[n];
    ll ret=n%P*(n%P+1)%P*inv2%P;
    for(ll i=2,pos;i<=n;i=pos+1)
    {
        pos=n/(n/i);
        ret=(ret-ask(n/i)%P*((pos-i+1)%P)%P+P)%P;
    }
    return PHI[n]=ret%P;
}

int main()
{
    ll n,ans=0;
    scanf("%lld",&n);sieve();
    for(ll i=1,pos,t,l;i<=n;i=pos+1)
    {
        pos=n/(n/i);t=((ask(pos)-ask(i-1))%P+P)%P;
        l=n/i%P;
        (ans+=l*l%P*t)%=P;
    }
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}