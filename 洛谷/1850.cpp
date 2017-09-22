#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;

double F[2010][2010][2];
int dis[310][310];
int c[2010],d[2010];
double k[2010];
const int INF=0x3f3f3f3f;
int n,m,v,e;
int main()
{
    int a,b,w;
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%d%d%d",&n,&m,&v,&e);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1;i<=n;i++) scanf("%lf",&k[i]);
    for(int i=1;i<=e;i++)
    {
        scanf("%d%d%d",&a,&b,&w);
        if(dis[a][b]>w)    dis[a][b]=dis[b][a]=w;
    }
    for(int i=1;i<=v;i++) dis[i][i]=0;
    for(int k=1;k<=v;k++)
        for(int i=1;i<=v;i++)
            for(int j=1;j<=v;j++)
                if(dis[i][k]!=INF&&dis[k][j]!=INF&&dis[i][j]>dis[i][k]+dis[k][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            F[i][j][0]=F[i][j][1]=1e9;
    F[1][0][0]=F[1][1][1]=0;
    for(int i=2;i<=n;i++)
    {
        F[i][0][0]=F[i-1][0][0]+dis[c[i-1]][c[i]];
        for(int j=1;j<=min(i,m);j++)
        {
            F[i][j][0]=min(F[i-1][j][0]+dis[c[i-1]][c[i]],
                F[i-1][j][1]
                +dis[c[i-1]][c[i]]*(1-k[i-1])
                +dis[d[i-1]][c[i]]*k[i-1]);
            F[i][j][1]=min(F[i-1][j-1][0]
                +dis[c[i-1]][c[i]]*(1-k[i])
                +dis[c[i-1]][d[i]]*k[i],
                F[i-1][j-1][1]
                +dis[c[i-1]][c[i]]*(1-k[i-1])*(1-k[i])
                +dis[c[i-1]][d[i]]*(1-k[i-1])*k[i]
                +dis[d[i-1]][c[i]]*k[i-1]*(1-k[i])
                +dis[d[i-1]][d[i]]*k[i-1]*k[i]);
        }
    }
    double ans=1e9;
    for(int i=0;i<=m;i++) ans=min(ans,min(F[n][i][0],F[n][i][1]));
    printf("%.2lf\n",ans);
}
