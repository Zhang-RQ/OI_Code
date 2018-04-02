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
const int MAXS=1<<10;
ll  C[101][101];
ll siz[MAXS],cnt[MAXS],e[11];
ll f[MAXS][51],g[MAXS][51];
int n,m,u,v;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);u--;v--;
        e[u]|=1<<v;e[v]|=1<<u;
    }
    for(int i=0;i<=m;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    for(int s=0;s<(1<<n);s++)
    {
        siz[s]=siz[s>>1]+(s&1);
        for(int i=0;i<n;i++)
            if((s>>i)&1)
                cnt[s]+=siz[s&e[i]];
        cnt[s]>>=1;
        int lowbit=s&-s;
        for(int t=(s-1)&s;t;t=(t-1)&s)
            if(t&lowbit)
                for(int i=0;i<=cnt[t];++i)
                    for(int j=0;j<=cnt[s^t];++j)
                        f[s][i+j]+=g[t][i]*C[cnt[s^t]][j];
        for(int i=0;i<=cnt[s];++i)
            g[s][i]=C[cnt[s]][i]-f[s][i];
    }
    double ans=0;
    for(int i=0;i<=m;i++)
        ans+=1.0*f[(1<<n)-1][i]/C[m][i];
    ans/=m+1;
    printf("%.6lf\n",ans);
}
