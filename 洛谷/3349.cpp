#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC target("avx")
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
const int MAXN=17;
const int MAXM=40;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
unsigned char mp[20][20];
ll f[20][20],sum,ans;
int n,m,a[20],cnt,x,y;
void dfs(int x,int fa)
{
    for(int i=1;i<=cnt;i++) f[x][i]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        for(int j=1;j<=cnt;j++)
        {
            ll tmp=0;
            for(int k=1;k<=cnt;k++)
                if(mp[a[j]][a[k]]) tmp+=f[v][k];
            f[x][j]*=tmp;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&x,&y),mp[x][y]=mp[y][x]=1;
    for(int i=1;i<n;i++)  scanf("%d%d",&x,&y),add(x,y),add(y,x);
    for(int s=1;s<(1<<n);s++)
    {
        cnt=sum=0;
        for(int i=0;i<=n-1;i++) if((s>>i)&1)  a[++cnt]=i+1;
        dfs(1,0);
        for(int i=1;i<=cnt;i++) sum+=f[1][i];
        if((n-cnt)&1) ans-=sum;
        else ans+=sum;
    }
    printf("%lld\n",ans);
}
