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
struct node{
    int v,cost,flow,nxt;
}Edge[100010];
int head[6000],cnt=1;
void add(int u,int v,int flow,int cost)
{
    Edge[++cnt].v=v;
    Edge[cnt].flow=flow;
    Edge[cnt].cost=cost;
    Edge[cnt].nxt=head[u];
    head[u]=cnt;
}
int dis[6000],inq[6000];
int pre[6000],preedge[6000];
int tmpflow[6000];
int s,t,n,m;
bool bfs()
{
    queue<int> q;
    memset(inq,0,sizeof(inq));
    memset(tmpflow,0,sizeof(tmpflow));
    memset(dis,0x3f,sizeof(dis));
    tmpflow[s]=(1<<30);
    q.push(s);inq[s]=1;dis[s]=0;
    while(q.size())
    {
        int x=q.front();q.pop();
        inq[x]=0;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!Edge[i].flow||dis[v]<=dis[x]+Edge[i].cost)
                continue;
            dis[v]=dis[x]+Edge[i].cost;
            pre[v]=x;
            preedge[v]=i;
            tmpflow[v]=min(tmpflow[x],Edge[i].flow);
            if(!inq[v])
                q.push(v),inq[v]=1;
        }
    }
    return dis[t]!=0x3f3f3f3f;
}
int t1,t2,t3,t4;
int maxflow,mincost;
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
        add(t1,t2,t3,t4);
        add(t2,t1,0,-t4);
    }
    while(bfs())
    {
        int tmp=t;
        while(tmp!=s)
        {
            Edge[preedge[tmp]].flow-=tmpflow[t];
            Edge[preedge[tmp]^1].flow+=tmpflow[t];
            tmp=pre[tmp];
        }
        mincost+=dis[t]*tmpflow[t];
        maxflow+=tmpflow[t];
    }
    printf("%d %d\n",maxflow,mincost);
}
