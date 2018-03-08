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
const int MAXN=10000100;
int prime[MAXN],cnt,mu[MAXN],t,n,m,pos;
ll f[MAXN],ans;
bool vis[MAXN];
void sieve()
{
    mu[1]=1;
    for(int i=2;i<=MAXN;i++)
    {
        if(!vis[i]) {prime[++cnt]=i;mu[i]=-1;}
        for(int j=1;i*prime[j]<=MAXN&&j<=cnt;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)  {mu[i*prime[j]]=0;break;}
            else mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=cnt;i++)
        for(int j=1;j*prime[i]<=MAXN;j++)
            f[prime[i]*j]+=mu[j];
    for(int i=1;i<=MAXN;i++) f[i]+=f[i-1];
}
int main()
{
    sieve();
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        ans=0;
        for(int i=1;i<=min(n,m);i=pos+1)
        {
            pos=min(n/(n/i),m/(m/i));
            ans+=1ll*(n/i)*(m/i)*(f[pos]-f[i-1]);
        }
        printf("%lld\n",ans);
    }
}
