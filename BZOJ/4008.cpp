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
const int MAXN=223;
int n,r;
double f[MAXN][MAXN],pw[MAXN][MAXN],p[MAXN],pc[MAXN];
int d[MAXN],T;
void solve()
{
    memset(pc,0,sizeof pc);
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%d",&p[i],&d[i]);
        pw[i][0]=1;
        for(int j=1;j<=r;j++)
            pw[i][j]=pw[i][j-1]*(1-p[i]);
    }
    f[1][0]=pw[1][r];
    f[1][1]=pc[1]=1-pw[1][r];
    for(int i=2;i<=n;i++)
        for(int j=0;j<=n;j++)
        {
            f[i][j]=f[i-1][j]*pw[i][r-j];
            if(j) f[i][j]+=f[i-1][j-1]*(1-pw[i][r-j+1]);
        }
    for(int i=2;i<=n;i++)
        for(int j=0;j<=r;j++)
            pc[i]+=f[i-1][j]*(1-pw[i][r-j]);
    double ans=0;
    for(int i=1;i<=n;i++) ans+=pc[i]*d[i];
    printf("%.10lf\n",ans);
}
int main()
{
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}