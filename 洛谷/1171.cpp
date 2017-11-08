%:pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
using namespace std;
#define min(a,b) a<b?a:b
int f[(1<<20)+20][30];
int dis[30][30];
int n;
int main()
{
    memset(f,0x3f,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&dis[i][j]);
    f[1][1]=0;
    for(int s=1;s<=(1<<n)-1;s++)
        for(int i=1;i<=n;i++)
            if((s>>(i-1))&1)
                for(int j=1;j<=n;j++)
                    if((s>>(j-1))&1)
                        f[s][i]=min(f[s][i],f[s^(1<<(i-1))][j]+dis[j][i]);
    int ans=0x3f3f3f3f;
    for(int i=2;i<=n;i++)
        ans=min(ans,f[(1<<n)-1][i]+dis[i][1]);
    printf("%d\n",ans);
}
