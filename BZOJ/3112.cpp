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
double INF=100000000;
double eps=1E-8;
double a[1010][10100];
int n,m,l,r,d;
void Pivot(int l,int e)
{
    double t=a[l][e];a[l][e]=1;
    for(int i=0;i<=n;i++) a[l][i]/=t;
    for(int i=0;i<=m;i++) if(i!=l&&fabs(a[i][e])>eps)
    {
        t=a[i][e];a[i][e]=0;
        for(int j=0;j<=n;j++)
            a[i][j]-=a[l][j]*t;
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
        if(!e) return false;
        Pivot(l,e);
    }
    return true;
}
bool Simplex()
{
    int l=0,e=0;double mn=INF;
    while(true)
    {
        l=e=0;mn=INF;
        for(int i=1;i<=n;i++) if(a[0][i]>eps) {e=i;break;}
        if(!e) break;
        for(int i=1;i<=m;i++) if(a[i][e]>eps&&mn>a[i][0]/a[i][e])
            mn=a[i][0]/a[i][e],l=i;
        if(!l) return false;
        Pivot(l,e);
    }
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf",&a[i][0]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&l,&r,&d);
        for(int j=l;j<=r;j++)
            a[j][i]=1;
        a[0][i]=d;
    }
    swap(n,m);
    if(init()&&Simplex())
    {
        printf("%lld\n",(ll)floor(-a[0][0]+0.5));
    }
}
