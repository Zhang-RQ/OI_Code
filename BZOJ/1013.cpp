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
double A[15][15],inp[15][15];
double X[15];
int n;
const double eqs=1e-6;
inline double sqr(double &a)
{
    return a*a;
}
void init()
{
    //memset(A,0,sizeof(A));
    for(int i=1;i<=n+1;i++)
        for(int j=1;j<=n;j++)
            scanf("%lf",&inp[i][j]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            A[i][j]=2*(inp[i+1][j]-inp[i][j]);
            A[i][n+1]+=sqr(inp[i+1][j])-sqr(inp[i][j]);
        }
    }
}
void solve()
{
    for(int i=1;i<=n;i++)
    {
        int r=i;
        for(int j=i+1;j<=n;j++)
            if(fabs(A[j][i]>fabs(A[r][i]))) r=j;
        for(int j=1;j<=n+1;j++) swap(A[i][j],A[r][j]);
        for(int j=i+1;j<=n;j++)
        {
            double t=A[i][i]/A[j][i];
            for(int k=i;k<=n+1;k++)
            {
                A[j][k]*=t;
                A[j][k]-=A[i][k];
            }
        }
    }
    for(int i=n;i>=1;i--)
    {
        X[i]=A[i][n+1]/A[i][i];
        for(int j=1;j<=i;j++)
            A[j][n+1]-=X[i]*A[j][i];
    }
}
int main()
{
    scanf("%d",&n);
    init();
    solve();
    for(int i=1;i<=n-1;i++) printf("%.3lf ",X[i]);
    printf("%.3lf",X[n]);
}
