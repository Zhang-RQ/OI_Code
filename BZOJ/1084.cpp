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
void solve1(int n,int k)
{
    int in1[110],sum1[110];
    int f1[110][15];
    memset(f1,0xcf,sizeof(f1));
    sum1[0]=0;
    for (int i=0;i<=n;i++)
            for (int j=1;j<=k;j++) f1[i][j]=0xcfcfcfcf;
    for(int i=1;i<=n;i++)   scanf("%d",&in1[i]),sum1[i]=sum1[i-1]+in1[i],f1[i][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k;j++)
        {
            f1[i][j]=f1[i-1][j];
            for(int i1=0;i1<i;i1++)
            {
                f1[i][j]=max(f1[i][j],f1[i1][j-1]+sum1[i]-sum1[i1]);
            }
        }
    printf("%d\n",f1[n][k]);
}
int in[150][3];
int sum1[150],sum2[150];
int f[150][150][35];
void solve2(int n,int k)
{
    sum1[0]=sum2[0]=0;
    for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&in[i][1],&in[i][2]);
            sum1[i]=sum1[i-1]+in[i][1];
            sum2[i]=sum2[i-1]+in[i][2];
        }
        for (int i=0;i<=n;i++)
            for (int j=0;j<=n;j++)
                for (int k1=1;k1<=k;k1++) f[i][j][k1]=0xcfcfcfcf;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k1=1;k1<=k;k1++)
            {
                f[i][j][k1]=max(f[i-1][j][k1],f[i][j-1][k1]);
                for(int i1=0;i1<i;i1++)
                    f[i][j][k1]=max(f[i][j][k1],f[i1][j][k1-1]+sum1[i]-sum1[i1]);
                for(int j1=0;j1<j;j1++)
                    f[i][j][k1]=max(f[i][j][k1],f[i][j1][k1-1]+sum2[j]-sum2[j1]);
                if(i==j)    for(int i1=0;i1<i;i1++)
                {
                    f[i][j][k1]=max(f[i][j][k1],f[i1][i1][k1-1]+sum1[i]+sum2[i]-sum1[i1]-sum2[i1]);
                }
            }
    for (int i=1;i<=n;i++)
            {
                for (int j=1;j<=n;j++)
                {
                    for (int k1=1;k1<=k;k1++)
                        {
                            printf("%d ",f[i][j][k1]);
                        }
                        printf("     ");
                }
                printf("\n");
                }
    printf("%d\n",f[n][n][k]);
}
int main()
{
    int n,k,m;
    scanf("%d%d%d",&n,&m,&k);
    if(m==1) solve1(n,k);
    if(m==2) solve2(n,k);
    return 0;

}
