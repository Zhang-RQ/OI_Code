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

const int MAXN=1E3+5;
const int MAXM=2E3+5;

struct __edge{
    int nxt,v;
}Edge[MAXM];

int head[MAXN],cnt_e,siz[MAXN],n;
int f[MAXN][MAXN*5],t[MAXN*5],val[MAXN];

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

int dfs(int x,int fa)
{
    f[x][0]=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        if(Edge[i].v==fa) continue;
        int v=Edge[i].v,w=dfs(v,x);
        memcpy(t,f[x],sizeof t);memset(f[x],0x3f,sizeof f[x]);
        for(int j=0;j<=val[x];j++)
        {
            if(j+val[v]<=val[x]) f[x][j+val[v]]=min(f[x][j+val[v]],t[j]+w);
            if(j+w<=val[x]) f[x][j+w]=min(f[x][j+w],t[j]+val[v]);
        }
    }
    int ret=0x3f3f3f3f;
    for(int j=0;j<=val[x];j++) ret=min(ret,f[x][j]);
    return ret;
}

int main()
{
    scanf("%d",&n);
    for(int i=2,x;i<=n;i++) scanf("%d",&x),add(x,i),add(i,x);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    int ans=dfs(1,0);
    puts(ans==0x3f3f3f3f?"IMPOSSIBLE":"POSSIBLE");
    #ifdef LOCAL
        system("pause");
    #endif
}