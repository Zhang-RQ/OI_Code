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
const int MAXN=50100;
const int MAXM=1E6+10;
const int INF=1<<30;
#define id(x,y) (x)+(y-1)*100
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
int lvl[MAXN],n,m,s=0,t=MAXN-4;
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
int val;
ll ans,tot;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&val),add(s,id(i,j),val,0),ans+=val;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&val),add(id(i,j),t,val,0),ans+=val;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&val);
            add(s,id(i,j)+10000,val,0);ans+=val;
            add(id(i,j)+10000,id(i,j),INF,0);
            if(i!=1) add(id(i,j)+10000,id(i-1,j),INF,0);
            if(i!=n) add(id(i,j)+10000,id(i+1,j),INF,0);
            if(j!=1) add(id(i,j)+10000,id(i,j-1),INF,0);
            if(j!=m) add(id(i,j)+10000,id(i,j+1),INF,0);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&val);
            add(id(i,j)+20000,t,val,0);ans+=val;
            add(id(i,j),id(i,j)+20000,INF,0);
            if(i!=1) add(id(i-1,j),id(i,j)+20000,INF,0);
            if(i!=n) add(id(i+1,j),id(i,j)+20000,INF,0);
            if(j!=1) add(id(i,j-1),id(i,j)+20000,INF,0);
            if(j!=m) add(id(i,j+1),id(i,j)+20000,INF,0);
        }
    while(bfs())
        tot+=dfs(s,INF);
    printf("%lld\n",ans-tot);
}
