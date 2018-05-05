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
const int P=1E9+7;
const int MAXN=1E6;
int n,m,T,mu[MAXN+10],prime[MAXN+10],tot;
ll f[MAXN+10],F[MAXN+10],invf[MAXN+10],prod[MAXN+10],invprod[MAXN+10];
bool vis[MAXN+10];
ll ksm(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) (ret*=a)%=P;
        (a*=a)%=P;
        b>>=1;
    }
    return ret;
}
void init()
{
    F[1]=F[2]=invf[1]=invf[2]=f[1]=f[2]=1;mu[1]=1;
    for(int i=3;i<=MAXN;i++) f[i]=(f[i-2]+f[i-1])%P,invf[i]=ksm(f[i],P-2),F[i]=1;
    for(int i=2;i<=MAXN;i++)
    {
        if(!vis[i]) prime[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&1ll*prime[j]*i<=MAXN;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) {mu[i*prime[j]]=0;break;}
            else mu[i*prime[j]]=-mu[i];
        }
    }
    invprod[0]=prod[0]=1;
    for(int i=1;i<=MAXN;i++)
    {
        if(mu[i]!=0) for(int j=i;j<=MAXN;j+=i) F[j]=(F[j]*(mu[i]==1?f[j/i]:invf[j/i]))%P;
        prod[i]=prod[i-1]*F[i]%P;
    }
    invprod[MAXN]=ksm(prod[MAXN],P-2);
    for(int i=MAXN-1;i>=1;i--) invprod[i]=invprod[i+1]*F[i+1]%P;
}
int main()
{
    init();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        int pos=0;
        ll ans=1;
        for(int k=1;k<=min(n,m);k=pos+1)
        {
            pos=min(n/(n/k),m/(m/k));
            ans=ans*ksm(prod[pos]*invprod[k-1]%P,1ll*(n/k)*(m/k))%P;
        }
        printf("%lld\n",ans);
    }
}
