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
const int MAXN=5100;
const int MAXM=1E6+10;
const ll INF=1ll<<60;
struct node{
    int nxt,v;ll w;
}Edge[MAXM];
int head[MAXN],cnt_e=1,u,v;
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
int lvl[MAXN],n,m,s=0,t=MAXN-1,T,val;
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
ll ans=0,tmp=0,ans1,num;
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        cnt_e=1;memset(head,0,sizeof head);ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&val);
            if(val>0) add(s,i,val*10000ll-1,0),ans+=val,++num;
            else add(i,t,-val*10000ll+1,0);
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            add(u,v,INF,0);
        }
        while(bfs())
            tmp+=dfs(s,INF);
        ans1=(tmp+num)%10000;ans-=(tmp+num)/10000;
        printf("%lld %lld\n",ans1,ans);
    }
}
