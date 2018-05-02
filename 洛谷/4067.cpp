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
typedef std::pair<long long,long long> pll;
using namespace std;
int T,mxt;
ll n,m,k,p;
pll f[70][2][2][2];
bool vis[70][2][2][2];
pll dfs(int x,bool limn,bool limm,bool limk)
{
    if(x>mxt) return make_pair(1,0);
    if(vis[x][limn][limm][limk]) return f[x][limn][limm][limk];
    vis[x][limn][limm][limk]=1;
    pll ret=make_pair(0,0);
    int np=(n>>(mxt-x))&1,mp=(m>>(mxt-x))&1,kp=(k>>(mxt-x))&1;
    for(int i=0;i<=(limn?np:1);i++)
        for(int j=0;j<=(limm?mp:1);j++)
        {
            if(limk&&kp>(i^j)) continue;
            pll t=dfs(x+1,limn&&i==np,limm&&j==mp,limk&&(i^j)==kp);
            (ret.first+=t.first)%=p;
            (ret.second+=(1ll<<(mxt-x))%p*(i^j)%p*t.first%p+t.second)%=p;
        }
    return f[x][limn][limm][limk]=ret;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld",&n,&m,&k,&p);n--;m--;
        memset(vis,0,sizeof vis);
        mxt=0;
        mxt=max(mxt,64-__builtin_clzll(n));
        mxt=max(mxt,64-__builtin_clzll(m));
        mxt=max(mxt,64-__builtin_clzll(k));
        dfs(1,1,1,1);
        printf("%lld\n",(f[1][1][1][1].second-k%p*f[1][1][1][1].first%p+p)%p);
    }
}
