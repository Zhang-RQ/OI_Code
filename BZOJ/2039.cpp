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
const int MAXN=8100;
const int MAXM=3E6+10;
const ll INF=1ll<<60;
struct node{
    int nxt,v;ll w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,ll w,ll w2)
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
int lvl[MAXN],n,m,s=0,t=MAXN-3,T;
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
ll dfs(int x,ll flow)
{
    if(x==t) return flow;
    ll add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)
            continue;
        ll min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int E[1001][1001],a[1001];
ll sum[1001],ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&E[i][j]),sum[i]+=E[i][j],ans+=E[i][j];
    for(int i=1;i<=n;i++)
        add(s,i,sum[i],0),add(i,t,a[i],0);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            add(i,j,E[i][j]*2,E[i][j]*2);
    while(bfs())
        ans-=dfs(s,INF);
    printf("%lld\n",ans);
}
