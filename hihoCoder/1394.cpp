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
const int MAXN=2010;
const int MAXM=1E5+10;
struct node{
    int nxt,u,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    Edge[cnt_e].u=u;
    head[u]=cnt_e;
}
int lvl[MAXN],n,m,s=0,t=MAXN-2,u,v;
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
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        add(s,i,1),add(i,s,0),
        add(i+510,t,1),add(t,i+510,0);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&u,&v),add(u,v+510,1),add(v+510,u,0);
    int ans=n;
    while(bfs())
        ans-=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
