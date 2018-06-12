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
const int MAXN=50010;
int mu[MAXN],s[MAXN],pri[MAXN],tot;
bool vis[MAXN];
void sieve()
{
    mu[1]=1;
    for(int i=2;i<=50000;i++)
    {
        if(!vis[i]) pri[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*pri[j]<=50000;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) {mu[i*pri[j]]=0;break;}
            else mu[i*pri[j]]=-mu[i];
        }
    }
    for(int i=1;i<=50000;i++)
        mu[i]+=mu[i-1];
    for(int i=1,pos;i<=50000;i++)
    {
        s[i]=pos=0;
        for(int j=1;j<=i;j=pos+1)
        {
            pos=i/(i/j);
            s[i]+=(pos-j+1)*(i/j);
        }
    }
}
void solve()
{
    int n,m,lim;
    ll ans=0;
    scanf("%d%d",&n,&m);
    lim=min(n,m);
    for(int i=1,pos;i<=lim;i=pos+1)
    {
        pos=min(n/(n/i),m/(m/i));
        ans+=1ll*(mu[pos]-mu[i-1])*s[n/i]*s[m/i];
    }
    printf("%lld\n",ans);
}
int main()
{
    int T;
    for(sieve(),scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}