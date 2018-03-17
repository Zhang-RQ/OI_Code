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
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct node{
    int nxt,v;
    ll w;
}Edge[MAXM];
int n,m,u,v;
ll w;
int head[MAXN],cnt_e,cnt;
ll dis[MAXN],lop[MAXM],b[64];
bool vis[MAXN];
inline void add(int u,int v,ll w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
void dfs(int x,int fa)
{
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        if(vis[v]) {lop[++cnt]=dis[x]^dis[v]^Edge[i].w;continue;}
        dis[v]=dis[x]^Edge[i].w;
        dfs(v,x);
    }
}
void build()
{
    for(int i=1;i<=cnt;i++)
        for(int j=62;~j;j--)
            if(lop[i]>>j&1)
            {
                if(b[j]) lop[i]^=b[j];
                else
                {
                    b[j]=lop[i];
                    for(int k=j-1;k>=1;k--) if(b[k]&&b[j]>>k&1) b[j]^=b[k];
                    for(int k=j+1;k<=62;k++) if(b[k]>>j&1) b[k]^=b[j];
                    break;
                }
            }
}
ll solve(ll s)
{
    ll ret=s;
    for(int i=62;~i;i--)
        if((ret^b[i])>ret)
            ret^=b[i];
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dfs(1,0);
    build();
    printf("%lld\n",solve(dis[n]));
}
