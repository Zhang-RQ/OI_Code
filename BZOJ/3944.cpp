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

const int siz=(2500010);

map<ll,pair<ll,ll> > mp;

ll n;
bool vis[siz+3];
int pri[siz+3],tot;
ll phi[siz+3],mu[siz+3];

void init()
{
    phi[1]=mu[1]=1;
    for(int i=2;i<=siz;i++)
    {
        if(!vis[i]) pri[++tot]=i,phi[i]=i-1,mu[i]=-1;
        for(int j=1;j<=tot&&1ll*pri[j]*i<=siz;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];mu[i*pri[j]]=0;break;}
            else phi[i*pri[j]]=phi[i]*(pri[j]-1),mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<=siz;i++) phi[i]+=phi[i-1],mu[i]+=mu[i-1];
}

pair<ll,ll> ask(ll x)
{
    if(x<=siz) return make_pair(phi[x],mu[x]);
    if(mp.find(x)!=mp.end()) return mp[x];
    ll MU=1,PHI=x*(x+1)/2,pos;
    pair<ll,ll> t;
    for(ll d=2;d<=x;d=pos+1)
    {
        pos=x/(x/d);t=ask(x/d);
        PHI-=(pos-d+1)*t.first;MU-=(pos-d+1)*t.second;
    }
    return mp[x]=make_pair(PHI,MU);
}

void solve()
{
    scanf("%lld",&n);
    pair<ll,ll> t=ask(n);
    printf("%lld %lld\n",t.first,t.second);
}

int main()
{
    int T;init();
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}