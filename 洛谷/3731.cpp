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
const int MAXN=1E4+5;
const int MAXM=150010;
struct __edge{
    int nxt,v,f,u;
}Edge[MAXM<<2];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int f)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].u=u;
    Edge[cnt_e].f=f;
    head[u]=cnt_e;
}
int lvl[MAXN],S,T=MAXN-1,bl[MAXN],dfn[MAXN],low[MAXN],SCC,stk[MAXN],top,tot,u,v;
int n,m;
bool ins[MAXN];
queue<int> q;
std::vector<pair<int,int> > ans;
bool bfs()
{
    q.push(S);
    memset(lvl,0,sizeof lvl);
    lvl[S]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].f) continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[T]!=0;
}
int dfs(int x,int cur)
{
    if(x==T) return cur;
    int add_flow=0;
    for(int i=head[x];i&&cur>add_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].f) continue;
        int min_flow=dfs(v,min(cur-add_flow,Edge[i].f));
        if(!min_flow) lvl[v]=0;
        Edge[i].f-=min_flow;
        Edge[i^1].f+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++tot;
    stk[++top]=x;ins[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        if(!Edge[i].f) continue;
        int v=Edge[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x])
    {
        ++SCC;
        while(stk[top]!=x)
        {
            ins[stk[top]]=0;
            bl[stk[top]]=SCC;
            top--;
        }
        top--;
        bl[x]=SCC;
        ins[x]=0;
    }
}
namespace Bipartite{
    struct __edge{
        int nxt,v;
    }Edge[MAXM];
    int head[MAXN],cnt_e,col[MAXN];
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
    void dfs(int x)
    {
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(col[v]) continue;
            col[v]=col[x]^1;
            dfs(v);
        }
    }
    void build()
    {
        for(int i=1;i<=n;i++)
        {
            if(col[i]) continue;
            col[i]=2;dfs(i);
        }
        for(int i=1;i<=n;i++)
        {
            if(col[i]==2)
            {
                for(int k=head[i];k;k=Edge[k].nxt)  ::add(i,Edge[k].v,1),::add(Edge[k].v,i,0);
                ::add(S,i,1),::add(i,S,0);
            }
            else ::add(i,T,1),::add(T,i,0);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        Bipartite::add(u,v);
        Bipartite::add(v,u);
    }
    Bipartite::build();
    while(bfs()) dfs(S,0x3f3f3f3f);
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=2;i<=cnt_e;i+=2)
    {
        if(Edge[i].f) continue;
        u=Edge[i].u;v=Edge[i].v;
        if(u>v) swap(u,v);
        if(u==S||v==T) continue;
        if(bl[u]!=bl[v]) ans.push_back(make_pair(u,v));
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    for(auto i : ans)
        printf("%d %d\n",i.first,i.second);
}
