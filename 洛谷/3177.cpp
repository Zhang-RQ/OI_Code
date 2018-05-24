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
const int MAXN=2E3+5;
const int MAXM=4E3+5;
struct __edge{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e;
ll f[2010][2010],g[2010];
int n,k,siz[MAXN];
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
void dfs(int x,int fa)
{
    siz[x]=1;f[x][0]=f[x][1]=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        for(int j=0;j<=siz[x]&&j<=k;j++) g[j]=f[x][j];
        for(int j=0;j<=siz[x]&&j<=k;j++)
            for(int l=0;l<=siz[v]&&j+l<=k;l++)
                f[x][j+l]=max(f[x][j+l],g[j]+f[v][l]+1ll*Edge[i].w*l*(k-l)+1ll*Edge[i].w*(siz[v]-l)*(n-k-siz[v]+l));
        siz[x]+=siz[v];
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    dfs(1,0);
    printf("%lld\n",f[1][k]);
    #ifdef LOCAL
        system("pause");
    #endif
}