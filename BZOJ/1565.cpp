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
#define id(x,y) (x-1)*m+(y)
const int MAXN=1010;
const int MAXM=2E6+5;
int in[MAXN];
struct Graph{
    struct node{
        int nxt,v,u;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v)
    {
        // printf("%d %d\n",u,v);
        ++in[v];
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        Edge[cnt_e].u=u;
        head[u]=cnt_e;
    }
}G;
int DFN[MAXN],LOW[MAXN],n,m,val[MAXN],w,v,x,y,cnt;
bool ok[MAXN];
const int INF=1<<30;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
ll ans;
queue<int> q;
inline void add(int u,int v,int w,int w2)
{
    // printf("%d %d %d\n",u,v,w);
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    Edge[cnt_e].w=w2;
    head[v]=cnt_e;
}
int lvl[MAXN],s=0,t=MAXN-1;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof lvl);
    lvl[s]=1;q.push(s);
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].w)
                continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,int flow)
{
    if(x==t) return flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)
            continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
void topo()
{
    while(!q.empty())
    {
        int x=q.front();q.pop();
        ok[x]=1;
        for(int i=G.head[x];i;i=G.Edge[i].nxt)
        {
            int v=G.Edge[i].v;
            if(!(--in[v])) q.push(v);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d%d",&val[id(i,j)],&w);
            for(int k=1;k<=w;k++)
            {
                scanf("%d%d",&x,&y);x++,y++;
                G.add(id(i,j),id(x,y));
            }
            if(j!=1)
                G.add(id(i,j),id(i,j-1));
        }
    for(int i=1;i<=n*m;i++)
        if(!in[i])  q.push(i);
    topo();
    // for(int i=1;i<=n;i++)
    // {
    //     for(int j=1;j<=m;j++)
    //         printf("%d ",ok[id(i,j)]);
    //     puts("");
    // }
    for(int i=1;i<=n*m;i++)
        if(ok[i])
        {
            if(val[i]>0) add(s,i,val[i],0),ans+=val[i];
            else add(i,t,-val[i],0);
        }
    for(int i=1;i<=G.cnt_e;i++)
        if(ok[G.Edge[i].u]&&ok[G.Edge[i].v])
            add(G.Edge[i].v,G.Edge[i].u,INF,0);
    while(bfs())
        ans-=dfs(s,INF);
    printf("%lld\n",ans);
}
