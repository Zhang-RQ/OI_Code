#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXM 10100
#define MAXN 200010
#define INF 0x3f3f3f3f
int head[MAXM],lvl[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXN<<1];
int cnte=1;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int n,m,s,t,u,v,flow;
int dfs(int x,int cur_flow)
{
    if(x==t) return cur_flow;
    int addflow=0;
    for(int i=head[x];i&&addflow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if((!Edge[i].flow)||lvl[v]!=lvl[x]+1) continue;
        int minflow=dfs(v,min(cur_flow-addflow,Edge[i].flow));
        Edge[i].flow-=minflow;
        Edge[i^1].flow+=minflow;
        addflow+=minflow;
    }
    return addflow;
}
bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    queue<int> q;
    q.push(s);
    lvl[s]=1;
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        for(int i=head[tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||(!Edge[i].flow)) continue;
            lvl[v]=lvl[tmp]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int main()
{
    int ans=0;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&flow);
        add(u,v,flow);
        add(v,u,0);
    }
    while(bfs()) ans+=dfs(s,INF);
    printf("%d\n",ans);
}
