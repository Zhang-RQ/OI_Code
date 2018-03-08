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
const int MAXN=510;
const int MAXM=4E4+10;
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
int lvl[MAXN],n,m,s=1,t;
bool vis[MAXN];
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
int u,v,w,ans,flag,cnt;
std::vector<int> vs;
void bfs1()
{
    queue<int> q;
    q.push(s);vis[s]=1;vs.push_back(s);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(vis[v]||!Edge[i].w) continue;
            vis[v]=1;
            vs.push_back(v);
            q.push(v);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);t=n;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,0);
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    bfs1();
    printf("%d %d\n",ans,vs.size());
    for(auto i : vs)
        printf("%d ",i);
    puts("");
}
