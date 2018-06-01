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
#define R(i) for(int i=0;i<2;i++)
const int MAXN=1E5+5;
const int MAXM=1.5E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
inline void update(int &a,int b){a<b?(a=b):0;}
int f[MAXN][2][2],t[2][2],dfn[MAXN],cnt,fa[MAXN],n,m;
bool top[MAXN],bot[MAXN];
void dfs(int x,int father)
{
    dfn[x]=++cnt;fa[x]=father;
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=father&&dfn[Edge[i].v]) bot[x]=1;
    f[x][1][bot[x]]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        if(!dfn[v])
        {
            dfs(v,x);
            R(x) R(y) t[x][y]=0;
            R(j) R(k) R(a) R(b)
            {
                if(j&&a) continue;
                if(top[v]&&j&&b) continue;
                update(t[j][k|((!top[v])&b)],f[x][j][k]+f[v][a][b]);
            }
            R(j) R(k) f[x][j][k]=t[j][k];
        }
        else if(dfn[v]<dfn[x])
        {
            int xx=x;
            while(fa[xx]!=v) xx=fa[xx];
            top[xx]=1;
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(1,0);
    int ans=0;
    R(i) R(j) update(ans,f[1][i][j]);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}