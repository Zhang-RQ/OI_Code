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
const int MAXN=501;
const int MAXM=4E4+10;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int n,m,s=1,t,u,v,w;
int lvl[MAXN];
bool bfs()
{
    memset(lvl,0,sizeof lvl);
    queue<int> q;
    q.push(s);lvl[s]=1;
    while(!q.empty())
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
    for(int i=head[x];i&&flow>add_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w) continue;
        int min_flow=dfs(v,min(Edge[i].w,flow-add_flow));
        add_flow+=min_flow;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
    }
    return add_flow;
}
int main()
{
    scanf("%d%d",&n,&m);
    t=n;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,0);
    int ans=0;
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
