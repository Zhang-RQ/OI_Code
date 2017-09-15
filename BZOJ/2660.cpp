#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
int p[110];
long long dp[110][2];
long long f[110];
long long n;
int main()
{
    f[1]=1;
    f[2]=2;
    scanf("%lld",&n);
    int i;
    for(i=3;i;i++)
    {
        f[i]=f[i-1]+f[i-2];
        if(f[i]>=n) break;
    }
    for(;i;i--)
    {
        if(f[i]<=n)
        {
            n-=f[i];
            p[++p[0]]=i;
        }
    }
    reverse(p+1,p+1+p[0]);
    dp[1][1]=1;
    dp[1][0]=(p[1]-1)/2;
    for(int j=2;j<=p[0];j++)
    {
        dp[j][0]=dp[j-1][1]*((p[j]-p[j-1]-1)/2)+dp[j-1][0]*((p[j]-p[j-1])/2);
        dp[j][1]=dp[j-1][1]+dp[j-1][0];
    }
    printf("%lld\n",dp[p[0]][0]+dp[p[0]][1]);
}
