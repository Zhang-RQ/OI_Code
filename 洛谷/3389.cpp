#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
double A[110][110],X[110];
int n;
bool flag=0;
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
    for(int i=n;i>=1;i--) if(A[n][i]!=0) flag=1;
    if(!flag) {printf("No Solution\n");return;}
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
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++) scanf("%lf",&A[i][j]);
    solve();
    if(!flag) return 0;
    for(int i=1;i<=n;i++) printf("%.2lf\n",X[i]);
}
