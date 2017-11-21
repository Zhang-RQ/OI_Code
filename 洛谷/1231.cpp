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
const int MAXN=60010;
const int MAXM=200010;
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM];
int cnte=1;  //notice
inline void add(const int &u,const int &v,const int &val1,const int &val2)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val1;
    head[u]=cnte;
    Edge[++cnte].nxt=head[v];
    Edge[cnte].v=u;
    Edge[cnte].flow=val2;
    head[v]=cnte;
}
int N1,N2,N3,M1,M2,t1,t2;
int s=0,t=60000;
int lvl[MAXN];
bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;
    queue<int> q;
    q.push(s);
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
    if(x==t)
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
    int ans=0;
    scanf("%d%d%d",&N1,&N2,&N3);
    scanf("%d",&M1);
    for(int i=1;i<=N2;i++)
        add(s,i,1,0);
    for(int i=1;i<=N1;i++)
        add(i+15000,i+30000,1,0);
    for(int i=1;i<=M1;i++)
    {
        scanf("%d%d",&t1,&t2);
        add(t2,t1+15000,1,0);
    }
    scanf("%d",&M2);
    for(int i=1;i<=M2;i++)
    {
        scanf("%d%d",&t1,&t2);
        add(t1+30000,t2+45000,1,0);
    }
    for(int i=1;i<=N3;i++)
        add(i+45000,t,1,0);
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
    return 0;
}
