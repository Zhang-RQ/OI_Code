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
#define int ll
const int MAXN=12100;
const int MAXM=1E6+10;
const int INF=1ll<<60;
#define id(x,y) (x)+(y)*100
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
int lvl[MAXN],n,m,s=0,t=MAXN-1,T;
int mp[6][101][101];
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
signed main()
{
    ll sum=0;
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&mp[0][i][j]),sum+=mp[0][i][j],add(s,id(i,j),mp[0][i][j],0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&mp[1][i][j]),sum+=mp[1][i][j],add(id(i,j),t,mp[1][i][j],0);
    for(int i=1;i<=n-1;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&mp[2][i][j]),sum+=mp[2][i][j];
    for(int i=1;i<=n-1;i++)
        for(int j=1;j<=m;j++)
            scanf("%lld",&mp[3][i][j]),sum+=mp[3][i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-1;j++)
            scanf("%lld",&mp[4][i][j]),sum+=mp[4][i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m-1;j++)
            scanf("%lld",&mp[5][i][j]),sum+=mp[5][i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if((i+j)&1)
            {
                if(i!=1) add(s,id(i,j),mp[2][i-1][j],0),add(id(i,j),id(i-1,j),mp[2][i-1][j]+mp[3][i-1][j],0),add(id(i-1,j),t,mp[3][i-1][j],0);
                if(j!=1) add(s,id(i,j),mp[4][i][j-1],0),add(id(i,j),id(i,j-1),mp[4][i][j-1]+mp[5][i][j-1],0),add(id(i,j-1),t,mp[5][i][j-1],0);
                if(i!=n) add(s,id(i,j),mp[2][i][j],0),add(id(i,j),id(i+1,j),mp[2][i][j]+mp[3][i][j],0),add(id(i+1,j),t,mp[3][i][j],0);
                if(j!=m) add(s,id(i,j),mp[4][i][j],0),add(id(i,j),id(i,j+1),mp[4][i][j]+mp[5][i][j],0),add(id(i,j+1),t,mp[5][i][j],0);
            }
        }
    while(bfs())
        sum-=dfs(s,INF);
    printf("%lld\n",sum);
}
