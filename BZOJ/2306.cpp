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

const int MAXN=110;

int n,m,v0;
double rho,f[61][MAXN][MAXN],pw[61],val[MAXN],ans;

int main()
{
    memset(f,0xc2,sizeof f);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&val[i]),f[0][i][i]=0;
    scanf("%d%lf",&v0,&rho);
    pw[0]=rho;
    for(int i=1;i<=60;i++) pw[i]=pw[i-1]*pw[i-1];
    for(int i=1,u,v;i<=m;i++)
        scanf("%d%d",&u,&v),
        f[0][u][v]=val[v]*rho;
    for(int i=1;i<=60;i++)
        for(int k=1;k<=n;k++)
            for(int u=1;u<=n;u++)
                for(int v=1;v<=n;v++)
                    f[i][u][v]=max(f[i][u][v],f[i-1][u][k]+f[i-1][k][v]*pw[i-1]);
    for(int v=1;v<=n;v++)
        ans=max(ans,f[60][v0][v]);
    printf("%.1lf\n",ans+val[v0]);
    #ifdef LOCAL
        system("pause");
    #endif
}