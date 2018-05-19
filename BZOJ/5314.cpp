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
const int MAXN=1E5+5;
const int MAXM=2E5+5;
const int P=1E9+7;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,k,n,u,v,siz[MAXN];
int f[MAXN][101][2][2];
ll g[101][2][2];
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs(int x,int fa)
{
    f[x][0][0][0]=1;
    f[x][1][0][1]=1;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        for(int j=0,lim=min(siz[x],k);j<=lim;j++)
        {
            g[j][0][0]=f[x][j][0][0],f[x][j][0][0]=0;
            g[j][0][1]=f[x][j][0][1],f[x][j][0][1]=0;
            g[j][1][0]=f[x][j][1][0],f[x][j][1][0]=0;
            g[j][1][1]=f[x][j][1][1],f[x][j][1][1]=0;
        }
        for(int j=0,lim1=min(siz[x],k);j<=lim1;j++)
            for(int l=0,lim2=min(siz[v],k);l+j<=k&&l<=lim2;l++)
            {
                (f[x][j+l][0][0]+=g[j][0][0]*f[v][l][1][0]%P)%=P;
                (f[x][j+l][0][1]+=g[j][0][1]*(1ll*f[v][l][1][0]+f[v][l][0][0])%P)%=P;
                (f[x][j+l][1][0]+=(g[j][1][0]*(1ll*f[v][l][1][0]+f[v][l][1][1])%P+g[j][0][0]*f[v][l][1][1]%P)%P)%=P;
                (f[x][j+l][1][1]+=(g[j][0][1]*(1ll*f[v][l][0][1]+f[v][l][1][1])%P+g[j][1][1]*(1ll*f[v][l][0][0]+f[v][l][0][1]+f[v][l][1][0]+f[v][l][1][1])%P)%P)%=P;
            }
        siz[x]+=siz[v];
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(1,0);
    printf("%lld\n",(1ll*f[1][k][1][1]+f[1][k][1][0])%P);
    #ifdef LOCAL
        system("pause");
    #endif
}