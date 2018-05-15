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
const int MAXN=2E6+10;
int phi[MAXN],mu[MAXN],n,pri[MAXN],tot,p[MAXN],T;
ll f[MAXN],ans;
bool vis[MAXN];
void solve()
{
    scanf("%d",&n);tot=0;
    memset(vis,0,sizeof vis);
    memset(f,0,sizeof f);
    memset(p,0,sizeof p);
    phi[1]=mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) pri[++tot]=i,mu[i]=-1,phi[i]=i-1;
        for(int j=1;j<=tot&&pri[j]*i<=n;j++)
        {
            vis[pri[j]*i]=1;
            if(i%pri[j]==0) {mu[i*pri[j]]=0;phi[i*pri[j]]=phi[i]*pri[j];break;}
            else mu[i*pri[j]]=-mu[i],phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
    for(int i=1;i<=n;i++) ++p[phi[i]];
    ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            f[i]+=p[j];
    for(int i=1;i<=n;i++) f[i]=f[i]*f[i];
    for(int i=1;i<=n;i++)
        if(mu[i])
            for(int j=1;i*j<=n;j++)
                ans+=mu[i]*f[i*j]*phi[j];
    printf("%lld\n",ans);
}
int main()
{
    scanf("%d",&T);
    while(T--) solve();
}
