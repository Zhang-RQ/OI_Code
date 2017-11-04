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
#define MAXN 410
ll mp[MAXN][MAXN],sum[MAXN][MAXN];
int n,m,P,cnt[1000010];
ll ans=0;
int main()
{
    int su;
    freopen("maker.in","r",stdin);
    scanf("%d%d%d",&n,&m,&P);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&mp[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mp[i][j];
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
        {
            //memset(cnt,0,sizeof(cnt));
            cnt[0]=1;
            for(int k=1;k<=m;k++)
            {
                su=(sum[j][k]-sum[i-1][k])%P;
                ans+=cnt[su];
                ++cnt[su];
            }
            for(int k=1;k<=m;k++)
                cnt[(sum[j][k]-sum[i-1][k])%P]=0;
        }
    printf("%lld\n",ans);
}
