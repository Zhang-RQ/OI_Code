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
const int MAXN=5E4+5;
const int MAXM=2E7+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,fa[MAXN],dep[MAXN],ans,dfn[MAXN],cnt;
int tmp[MAXN<<1],low[MAXN],f[MAXN],tot,n,m;
deque<int> q;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void solve(int x,int y)
{
    q.clear();tot=dep[y]-dep[x]+1;
    for(int yy=y;yy!=x;yy=fa[yy]) tmp[tot--]=f[yy];
    tmp[1]=f[x];tot=dep[y]-dep[x]+1;
    for(int i=1;i<=tot;i++) tmp[i+tot]=tmp[i];
    q.push_front(1);
    for(int i=2;i<=(tot>>1)+tot;i++)
    {
        while(i-q.front()>(tot>>1)) q.pop_front();
        ans=max(ans,tmp[i]+tmp[q.front()]+i-q.front());
        while(q.size()&&tmp[q.back()]-q.back()<=tmp[i]-i) q.pop_back();
        q.push_back(i);
    }
    for(int i=2;i<=tot;i++) f[x]=max(f[x],tmp[i]+min(i-1,tot-i+1));
}
void dfs(int x,int fafa)
{
    fa[x]=fafa;dfn[x]=low[x]=++cnt;dep[x]=dep[fafa]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fafa) continue;
        if(!dfn[v]) dfs(v,x);
        low[x]=min(low[x],low[v]);
        if(low[v]>dfn[x]) ans=max(ans,f[x]+f[v]+1),f[x]=max(f[x],f[v]+1);
    }
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(fa[v]!=x&&dfn[v]>dfn[x]) solve(x,v);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,k;i<=m;i++)
    {
        scanf("%d%d",&k,&u);
        for(int j=2;j<=k;j++) scanf("%d",&v),add(u,v),add(v,u),u=v;
    }
    dfs(1,0);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}