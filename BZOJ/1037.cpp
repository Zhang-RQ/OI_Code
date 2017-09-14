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
int f[155][155][25][25];
int main()
{
    int n,m,k0;
    scanf("%d%d%d",&n,&m,&k0);
    f[0][0][0][0]=1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k1=0;k1<=min(i,k0);k1++)
                for(int k2=0;k2<=min(j,k0);k2++)
                {
                    if(i<n&&k1<k0)
                    {
                        f[i+1][j][k1+1][max(k2-1,0)]+=f[i][j][k1][k2];
                        f[i+1][j][k1+1][max(k2-1,0)]%=12345678;
                    }
                    if(j<m&&k2<k0)
                    {
                        f[i][j+1][max(k1-1,0)][k2+1]+=f[i][j][k1][k2];
                        f[i][j+1][max(k1-1,0)][k2+1]%=12345678;
                    }
                }
    int ans=0;
    for(int i=0;i<=k0;i++)
        for(int j=0;j<=k0;j++)
        {
            ans+=f[n][m][i][j];
            ans%=12345678;
        }
    printf("%d\n",ans);
}
