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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=100010;
int prime[MAXN],cnt;
ll phi[MAXN];
bool vis[MAXN];
void sieve()
{
    phi[1]=1;
    for(int i=2;i<=MAXN-2;i++)
    {
        if(!vis[i]) prime[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt&&prime[j]*i<=MAXN-2;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) {phi[prime[j]*i]=phi[i]*prime[j];break;}
            else phi[prime[j]*i]=phi[i]*(prime[j]-1);
        }
    }
    for(int i=2;i<=MAXN-2;i++)
        phi[i]+=phi[i-1];
}
int n,m,pos;
int main()
{
    sieve();
    scanf("%d%d",&n,&m);
    ll ans=0;
    for(int i=1;i<=min(n,m);i=pos+1)
    {
        pos=min(n/(n/i),m/(m/i));
        ans+=1ll*(n/i)*(m/i)*(phi[pos]-phi[i-1]);
    }
    ans=ans*2-1ll*m*n;
    printf("%lld\n",ans);
}
