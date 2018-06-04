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
const int MAXN=510;
const int MAXM=250010;
struct __edge{
    int u,v;
}Edge[MAXM];
double a[MAXN][MAXN],f[MAXN],res[MAXM];
double ans;
int n,m,du[MAXN];
void Gauss()
{
    for(int i=1;i<=n;i++)
    {
        int chs=i;
        for(int j=i;j<=n;j++)
            if(fabs(a[chs][i])<fabs(a[j][i]))
                chs=j;
        for(int j=1;j<=n+1;j++)
            swap(a[i][j],a[chs][j]);
        for(int j=i+1;j<=n;j++)
        {
            double t=a[j][i]/a[i][i];
            for(int k=1;k<=n+1;k++)
                a[j][k]-=a[i][k]*t;
        }
    }
    for(int i=n;i>=1;i--)
    {
        assert(a[i][i]!=0);
        f[i]=a[i][n+1]/a[i][i];
        for(int j=i-1;j>=1;j--)
            a[j][n+1]-=f[i]*a[j][i];
    }
    f[n]=0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&Edge[i].u,&Edge[i].v);
        du[Edge[i].u]++;du[Edge[i].v]++;
    }
    for(int i=1;i<=m;i++)
    {
        if(Edge[i].v!=n) a[Edge[i].u][Edge[i].v]=-1.0/du[Edge[i].v];
        if(Edge[i].u!=n) a[Edge[i].v][Edge[i].u]=-1.0/du[Edge[i].u];
    }
    for(int i=1;i<=n;i++)  a[i][i]=1;
    a[1][n+1]=1;
    Gauss();
    for(int i=1;i<=m;i++)
        res[i]=f[Edge[i].u]/du[Edge[i].u]+f[Edge[i].v]/du[Edge[i].v];
    sort(res+1,res+1+m);
    for(int i=1;i<=m;i++)
        ans+=res[i]*(m-i+1.0);
    printf("%.3lf\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}