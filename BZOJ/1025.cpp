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

const int MAXN=1010;

int n,tot,pri[MAXN];
ll ans,f[MAXN][MAXN];
bool vis[MAXN];

void sieve()
{
    for(int i=2;i<=1000;i++)
    {
	    if(!vis[i]) pri[++tot]=i;
        for(int j=1;j<=tot&&i*pri[j]<=1000;j++)
        {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break; 
        }
    }
}

void solve()
{
    f[0][0]=1;
    for(int i=1;i<=tot;i++)
    {
        for(int j=0;j<=n;j++)f[i][j]=f[i-1][j];
        for(int j=pri[i];j<=n;j*=pri[i])
            for(int k=0;k<=n-j;k++)
                f[i][k+j]+=f[i-1][k];
    }
    for(int i=0;i<=n;i++)ans+=f[tot][i];
}

int main()
{
    scanf("%d",&n);
    sieve();solve();
    printf("%lld\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}