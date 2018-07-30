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

const int MAXN=1010;
const double EPS=1E-6;

int n,fa[MAXN],x[MAXN],y[MAXN],k;
double dis[MAXN][MAXN];

inline void init(){for(int i=1;i<=n;i++) fa[i]=i;}

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

inline bool check(double x)
{
    init();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(dis[i][j]<x)
                fa[find(i)]=find(j);
    int cnt=0;
    for(int i=1;i<=n;i++)
        if(fa[i]==i) ++cnt;
    return cnt<k;
}

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dis[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    double L=0,R=100000000;
    while(R-L>EPS)
    {
        double mid=(L+R)/2;
        if(check(mid)) R=mid;
        else L=mid;
    }
    printf("%.2lf\n",L);
    #ifdef LOCAL
        system("pause");
    #endif
}