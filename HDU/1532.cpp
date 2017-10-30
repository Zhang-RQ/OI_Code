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
#define MAXM 410
#define MAXN 410
int head[MAXM];
struct Node{
    int flow,nxt,v;
}Edge[MAXN<<1];
int lvl[MAXN];
int cnte=1,m,n,t1,t2,t3,s=1,t;
const int INF=0x3f3f3f3f;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int dfs(int x,int cur_flow)
{
    if(x==t) return cur_flow;
    int addflow=0;
    for(int i=head[x];i&&addflow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if((!Edge[i].flow)||lvl[v]!=lvl[x]+1) continue;
        int minflow=dfs(v,min(Edge[i].flow,cur_flow-addflow));
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
    while(q.size())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||(!Edge[i].flow)) continue;
            lvl[v]=lvl[x]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}
int main()
{
    int ans=0;
    scanf("%d%d",&n,&m);
    t=m;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&t1,&t2,&t3);
        add(t1,t2,t3);
        add(t2,t1,0);
    }
    while(bfs()) ans+=dfs(s,INF);
    printf("%d\n",ans);
}
