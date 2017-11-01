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
#define MAXM 200010
#define MAXN 1000
const int INF=0x3f3f3f3f;
int n,s,t,t1,t2,t3,t4;
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM];
int cnte=1;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int lvl[MAXN];
bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    queue<int> q;
    q.push(s);lvl[s]=1;
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].flow) continue;
            q.push(v);
            lvl[v]=lvl[x]+1;
        }
    }
    return lvl[t]!=0;
}
int dfs(int x,int cur_flow)
{
    if(x==t) return cur_flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].flow)
            continue;
        int min_flow=dfs(v,min(cur_flow-add_flow,Edge[i].flow));
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    s=0;
    t=999;
    while(~scanf("%d",&n))
    {
        int ans=0;
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
        cnte=1;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&t1);
            for(int j=1;j<=t1;j++)
            {
                scanf("%d%d",&t3,&t4);
                add(i,400+(t3-1)*12+t4,1);
                add(400+(t3-1)*12+t4,i,0);
            }
        }
        for(int i=1;i<=n;i++)
            add(s,i,1),
            add(i,s,0);
        for(int i=1;i<=84;i++)
            add(i+400,t,1),
            add(t,i+400,0);
        while(bfs())
            ans+=dfs(s,INF);
        printf("%d\n",ans);
    }
}
