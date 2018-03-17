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
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int n,m,dfn[MAXN],low[MAXN],cnt,u,v,tot;
bool iscut[MAXN];
void dfs(int x,int fa)
{
    low[x]=dfn[x]=++cnt;
    int son=0;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!dfn[v])
        {
            ++son;
            dfs(v,x);
            low[x]=min(low[v],low[x]);
            if(low[v]>=dfn[x]) iscut[x]=1;
        }
        else if(v!=fa&&dfn[v]<dfn[x])
            low[x]=min(low[x],dfn[v]);
    }
    if(fa==0&&son==1) iscut[x]=0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&u,&v),
        add(u,v),add(v,u);
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i,0);
    for(int i=1;i<=n;i++) tot+=iscut[i];
    printf("%d\n",tot);
    for(int i=1;i<=n;i++)
        if(iscut[i]) printf("%d ",i);
    puts("");
}
