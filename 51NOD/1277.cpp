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

const int P=1E9+7;
const int MAXN=4E6+10;
const int inv2=500000004;
const int inv6=166666668;

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
        for(int j=1;j<=cnt&&i*pri[j]<MAXN;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {phi[i*pri[j]]=phi[i]*pri[j];break;}
            else phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
    for(int i=2;i<MAXN;i++)
        phi[i]=(phi[i-1]+phi[i]*i%P)%P;
}

ll ask(ll n)
{
    if(n<MAXN) return phi[n];
    if(PHI.find(n)!=PHI.end()) return PHI[n];
    ll ret=n%P*(n%P+1)%P*(2*n%P+1)%P*inv6%P;
    for(ll i=2,pos,l;i<=n;i=pos+1)
    {
        pos=n/(n/i);
        l=(pos-i+1)%P*((pos+i)%P)%P*inv2%P;
        ret=(ret-l*ask(n/i)%P+P)%P;
    }
    return PHI[n]=ret;
}

ll solve(ll n)
{
    ll ret=0;
    for(ll i=1,pos,l,t;i<=n;i=pos+1)
    {
        pos=n/(n/i);
        t=ask(n/i)%P;
        l=(pos-i+1)%P;
        (ret+=t*l%P)%=P;
    }
    return (ret*inv2%P+n%P*inv2%P)%P;
}

int main()
{
    ll L,R;sieve();
    cin>>L>>R;
    cout<<((solve(R)-solve(L-1))%P+P)%P<<endl;
    #ifdef LOCAL
        system("pause");
    #endif
}