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
#define MAXM 1000010
#define MAXN 3010
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM<<1];
int cnte=1;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int n,p,q,tmp,s=0,t=3000;
int lvl[MAXN];
bool bfs()
{
    queue<int> q;
    q.push(s);
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;
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
    if(x==t||!cur_flow)
        return cur_flow;
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
    scanf("%d%d%d",&n,&p,&q);
    for(int i=1;i<=p;i++)
        add(s,i,1),
        add(i,s,0);
    for(int i=1;i<=q;i++)
        add(i+1500,t,1),
        add(t,i+1500,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=p;j++)
        {
            scanf("%d",&tmp);
            if(!tmp)
                continue;
            add(j,i+400,1);
            add(i+400,j,0);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=q;j++)
        {
            if(j==1)
            {
                add(i+400,i+800,1);
                add(i+800,i+400,0);
            }
            scanf("%d",&tmp);
            if(!tmp)
                continue;
            add(i+800,j+1500,1);
            add(j+1500,i+800,0);
            }
    int ans=0;
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
