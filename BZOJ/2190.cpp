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
const int MAXN=40010;
int phi[MAXN],prime[MAXN],tot;
bool vis[MAXN];
void sieve()
{
    phi[1]=1;
    for(int i=2;i<MAXN;i++)
    {
        if(!vis[i]) prime[++tot]=i,phi[i]=i-1;
        for(int j=1;prime[j]*i<MAXN&&j<=tot;j++)
        {
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) {phi[i*prime[j]]=phi[i]*prime[j];break;}
            else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
int n;
ll ans=0;
int main()
{
    sieve();
    scanf("%d",&n);
    for(int i=1;i<n;i++)  ans+=phi[i];
    printf("%lld\n",ans<<1|1);
}
