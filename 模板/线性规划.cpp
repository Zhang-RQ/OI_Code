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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=25;
const double eps=1E-9;
const double INF=1000000000;
double a[MAXN][MAXN],ans[MAXN];
int id[MAXN<<1],n,m,t;
void Pivot(int l,int e)
{
    swap(id[n+l],id[e]);
    double t=a[l][e];a[l][e]=1;
    for(int i=0;i<=n;i++) a[l][i]/=t;
    for(int i=0;i<=m;i++) if(i!=l&&fabs(a[i][e])>eps)
    {
        t=a[i][e];a[i][e]=0;
        for(int j=0;j<=n;j++)
            a[i][j]-=t*a[l][j];
    }
}
bool init()
{
    int l=0,e=0;
    while(true)
    {
        l=e=0;
        for(int i=1;i<=m;i++) if(a[i][0]<-eps&&(!l||rand()&1)) l=i;
        if(!l) break;
        for(int i=1;i<=n;i++) if(a[l][i]<-eps&&(!e||rand()&1)) e=i;
        if(!e) {puts("Infeasible");return false;}
        Pivot(l,e);
    }
    return true;
}
bool Simplex()
{
    int l=0,e=0;
    double mn=INF;
    while(true)
    {
        l=e=0;mn=INF;
        for(int i=1;i<=n;i++)
            if(a[0][i]>eps) {e=i;break;}
        if(!e) break;
        for(int i=1;i<=m;i++)
            if(a[i][e]>eps&&mn>a[i][0]/a[i][e])
                mn=a[i][0]/a[i][e],l=i;
        if(!l) {puts("Unbounded");return false;}
        Pivot(l,e);
    }
    return true;
}
int main()
{
    srand((ull)new char);
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++)
        scanf("%lf",&a[0][i]);
    for(int i=1;i<=n;i++)  id[i]=i;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
            scanf("%lf",&a[i][j]);
        scanf("%lf",&a[i][0]);
    }
    if(init()&&Simplex())
    {
        printf("%.9lf\n",-a[0][0]);
        if(t)
        {
            for(int i=1;i<=m;i++)
                ans[id[n+i]]=a[i][0];
            for(int i=1;i<=n;i++)
                printf("%.9lf ",ans[i]);
            puts("");
        }
    }
}
