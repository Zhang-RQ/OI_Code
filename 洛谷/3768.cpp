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

const int M=8E6+10;
ll P,inv2,inv6;
ll phi[M],n;
int pri[M],tot;
bool vis[M];
map<ll,ll> PHI;

ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;b>>=1;
    }
    return ret;
}

void sieve()
{
    phi[1]=1;
    for(int i=2;i<=M-1;i++)
    {
        if(!vis[i]) pri[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&1ll*pri[j]*i<=M-1;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];break;}
            else phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
    for(int i=1;i<=M-1;i++)
        phi[i]=(phi[i-1]+phi[i]*i%P*i%P)%P;
}

inline ll s1(ll x){x%=P;return x*(x+1)%P*inv2%P;}
inline ll s2(ll x){x%=P;return x*(x+1)%P*(2*x%P+1)%P*inv6%P;}
inline ll s3(ll x){x%=P;return s1(x)*s1(x)%P;}

ll ask(ll x)
{
    if(x<M) return phi[x];
    if(PHI.find(x)!=PHI.end()) return PHI[x];
    ll ret=s3(x),pos;
    for(ll d=2;d<=x;d=pos+1)
    {
        pos=x/(x/d);
        ret=(ret-(s2(pos)-s2(d-1)+P)%P*ask(x/d)%P+P)%P;
    }
    (ret+=P)%=P;
    return PHI[x]=ret;
}

int main()
{
    scanf("%lld%lld",&P,&n);
    ll ans=0,pos;sieve();
    inv2=ksm(2,P-2);inv6=ksm(6,P-2);
    for(ll i=1;i<=n;i=pos+1)
    {
        pos=n/(n/i);
        ans=(ans+(ask(pos)-ask(i-1)+P)%P*s3(n/i))%P;
    }
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}