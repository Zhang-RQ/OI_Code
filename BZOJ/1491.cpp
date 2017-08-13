#include<cstdio>
#include<cstring>
using namespace std;
int dis[110][110];
double f[110],ans[110][110];
int main()
{
    memset(f,0,sizeof(f));
    memset(dis,0x3f3f3f3f,sizeof(dis));
    int u,v,w;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]=w;
        dis[v][u]=w;
        ans[u][v]=1;
        ans[v][u]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(i==j||j==k||i==k) continue;
                if(dis[i][k]+dis[k][j]<dis[i][j])
                {
                    ans[i][j]=ans[i][k]*ans[k][j];
                    dis[i][j]=dis[i][k]+dis[k][j];
                }else if(dis[i][k]+dis[k][j]==dis[i][j]) ans[i][j]+=ans[i][k]*ans[k][j];
            }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(i==j||j==k||i==k) continue;
                if(dis[i][k]+dis[k][j]==dis[i][j]) f[k]+=(ans[i][k]*ans[k][j])/ans[i][j];
            }
    for(int i=1;i<=n;i++) printf("%.3f\n",f[i]);
    return 0;
}
