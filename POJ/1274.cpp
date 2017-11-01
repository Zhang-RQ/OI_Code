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
const int INF=0x3f3f3f3f;
#define MAXM 40000
#define MAXN 10000
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM<<2];
int cnte=1;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int n,m,s,t;
int t1,t2;
int lvl[MAXN];
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
    q.push(s);
    lvl[s]=1;
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].flow)
                continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,int cur_flow)
{
    if(x==t)
        return cur_flow;
    int add_flow=0;
    for(int i=head[x];i&&cur_flow>add_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(!Edge[i].flow||lvl[v]!=lvl[x]+1)
            continue;
        int min_flow=dfs(v,min(Edge[i].flow,cur_flow-add_flow));
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        s=0;t=9999;cnte=1;
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&t1);
            for(int j=1;j<=t1;j++)
                scanf("%d",&t2),
                add(i,t2+4000,1),
                add(t2+4000,i,0);
        }
        for(int i=1;i<=n;i++)
            add(s,i,1),
            add(i,s,0);
        for(int i=1;i<=m;i++)
            add(i+4000,t,1),
            add(t,i+4000,0);
        while(bfs())
            ans+=dfs(s,INF);
        printf("%d\n",ans);
    }
}
