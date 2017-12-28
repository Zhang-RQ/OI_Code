#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN=100010;
int miu[MAXN],sum[MAXN],siz,vis[MAXN],prime[MAXN];
void get_miu()
{
    miu[1]=1;
    for(int i=2;i<MAXN-5;i++)
    {
        if(!vis[i])
            prime[++siz]=i,miu[i]=-1;
        for(int j=1;j<=siz&&prime[j]*i<MAXN-5;j++)
        {
            vis[prime[j]*i]=1;
            if(!(i%prime[j]))
                {miu[i*prime[j]]=0;break;}
            else miu[i*prime[j]]=-miu[i];
        }
    }
    for(int i=1;i<MAXN-5;i++)
        sum[i]=sum[i-1]+miu[i];
}
void solve(int N,int M,int D)
{
    int n=N/D,m=M/D;
    int lim=min(n,m);
    ll ans=0;
    for(int d=1;d<=lim;)
    {
        int pos=min(n/(n/d),m/(m/d));
        ans+=1ll*(sum[pos]-sum[d-1])*(n/d)*(m/d);
        d=pos+1;
    }
    printf("%lld\n",ans);
}
int T,_N,_M,_D;
int main()
{
    get_miu();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&_N,&_M,&_D);
        solve(_N,_M,_D);
    }
}
