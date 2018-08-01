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

const int MAXN=5E5+5;
const int MAXM=1E6+5;

struct __edge{
    int nxt,v,w;
}Edge[MAXM];

int head[MAXN],cnt_e,n,rt;

inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}

ll f[MAXN],g[MAXN];

void dfs(int x,int fa)
{
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa)  continue;
        dfs(v,x);
        g[x]=max(g[x],g[v]+Edge[i].w);
    }
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        f[x]+=f[v]+g[x]-(g[v]+Edge[i].w);
    }
}

int main()
{
    scanf("%d",&n);
    scanf("%d",&rt);
    for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    dfs(rt,0);
    printf("%lld\n",f[rt]);
    #ifdef LOCAL
        system("pause");
    #endif
}