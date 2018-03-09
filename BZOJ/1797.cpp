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
const int MAXN=6100;
const int MAXM=2E5+10;
const int INF=1<<30;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w,int w2)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
    Edge[++cnt_e].v=u;
    Edge[cnt_e].nxt=head[v];
    Edge[cnt_e].w=w2;
    head[v]=cnt_e;
}
int lvl[MAXN],n,m,s,t,T,DFN[MAXN],LOW[MAXN],cnt,SCC[MAXN],scccnt;
bool vis[MAXN],ins[MAXN];
stack<int> stk;
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
void bfs1()
{
    queue<int> q;
    q.push(s);vis[s]=1;
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            if(!Edge[i].w||vis[Edge[i].v]) continue;
            vis[Edge[i].v]=1;
            q.push(Edge[i].v);
        }
    }
}
void tarjan(int x)
{
    DFN[x]=LOW[x]=++cnt;stk.push(x);ins[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        if(!Edge[i].w) continue;
        int v=Edge[i].v;
        if(!DFN[v])
        {
            tarjan(v);
            LOW[x]=min(LOW[x],LOW[v]);
        }
        else if(ins[v]) LOW[x]=min(LOW[x],DFN[v]);
    }
    if(LOW[x]==DFN[x])
    {
        ++scccnt;
        while(1)
        {
            SCC[stk.top()]=scccnt;ins[stk.top()]=0;
            if(stk.top()==x) {stk.pop();break;}
            stk.pop();
        }
    }
}
int u,v,w;
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w,0);
    }
    while(bfs())
        dfs(s,INF);
    for(int i=1;i<=n;i++)
        if(!DFN[i])
            tarjan(i);
    for(int i=2;i<=cnt_e;i+=2)
    {
        if(Edge[i].w) puts("0 0");
        else
        {
            printf("%d ",SCC[Edge[i].v]!=SCC[Edge[i^1].v]);
            if(SCC[Edge[i^1].v]==SCC[s]&&SCC[Edge[i].v]==SCC[t]) printf("1\n");
            else printf("0\n");
        }
    }
}
