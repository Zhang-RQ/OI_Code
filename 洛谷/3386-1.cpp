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
#define MAXM 400010
#define MAXN 3010
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM<<1];
int cnte=1,n,m,e,t1,t2;
int s=0,t=3000;
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
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;q.push(s);
    while(!q.empty())
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
    int ans=0;
    scanf("%d%d%d",&n,&m,&e);
    for(int i=1;i<=e;i++)
    {
        scanf("%d%d",&t1,&t2);
        if(t1>n||t2>m)
            continue;
        add(t1,t2+1500,1),
        add(t2+1500,t1,0);
    }
    for(int i=1;i<=n;i++)
        add(s,i,1),
        add(i,s,0);
    for(int i=1;i<=m;i++)
        add(i+1500,t,1),
        add(t,i+1500,0);
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
