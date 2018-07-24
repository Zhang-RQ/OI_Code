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

const int MAXN=5E4+10;

int mu[MAXN],pri[MAXN],cnt;
bool vis[MAXN];

void sieve()
{
    mu[1]=1;
    for(int i=2;i<MAXN;i++)
    {
        if(!vis[i]) pri[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*pri[j]<MAXN;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {mu[i*pri[j]]=0;break;}
            else mu[i*pri[j]]=-mu[i];
        }
    }
}

inline ll calc(ll x)
{
    ll ret=0;int lim=sqrt(x);
    for(int i=1;i<=lim;i++) ret+=mu[i]*(x/(1ll*i*i));
    return ret;
}

inline void solve()
{
    int K;
    scanf("%d",&K);
    ll L=1,R=1644934081,ans;
    while(L<=R)
    {
        ll mid=(L+R)>>1;
        if(calc(mid)>=K) R=mid-1,ans=mid;
        else L=mid+1;
    }
    printf("%d\n",ans);
}

int main()
{
    int T;sieve();
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}