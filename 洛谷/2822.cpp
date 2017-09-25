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
ll C[2010][2010];
ll sum[2010][2010];
int n,m,k,t;
int main()
{
    scanf("%d%d",&t,&k);
    for(int i=0;i<=2000;i++) C[i][i]=1,C[i][0]=1;
    for(int i=1;i<=2000;i++)
        for(int j=1;j<i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%k;
    for(int i=1;i<=2000;i++)
    {
        for(int j=1;j<=2000;j++)
        {
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
            if(C[i][j]==0) sum[i][j]++;
        }
    }
    while(t--)
    {
        scanf("%d%d",&n,&m);
        printf("%lld\n",sum[n][m]);
    }
}
