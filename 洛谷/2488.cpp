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
const int INF=1<<30;
struct node{
    int v,nxt,flow,cost;
}Edge[725000];
int head[610],cnt=1;
int s=0,t=600;
void add(int u,int v,int flow,int cost)
{
    //if(cnt&1) printf("%d %d %d %d\n",u,v,flow,cost);
    Edge[++cnt].v=v;
    Edge[cnt].flow=flow;
    Edge[cnt].cost=cost;
    Edge[cnt].nxt=head[u];
    head[u]=cnt;
}
int inq[610],dis[610],pre[610],preedge[610],tmpflow[610];
bool bfs()
{
    queue<int> q;
    memset(inq,0,sizeof(inq));
    memset(dis,0x3f,sizeof(dis));
    memset(tmpflow,0,sizeof(tmpflow));
    tmpflow[s]=INF;
    dis[s]=0;q.push(s);inq[s]=1;
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
ll ans=0;
int n,m;
int t1,t2;
int T[10],W[10];
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t1);
        add(i+300,t,t1,0);
        add(t,i+300,0,0);
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&t1);
            if(t1)  add(i,j+300,INF,0),add(j+300,i,0,0);
        }
    for(int i=1;i<=m;i++)
    {
        T[0]=0;
        scanf("%d",&t1);
        for(int j=1;j<=t1;j++)
            scanf("%d",&T[j]);
        for(int j=1;j<=t1+1;j++)
            scanf("%d",&W[j]);
        for(int k=1;k<=t1;k++)
            add(s,i,T[k]-T[k-1],W[k]),
            add(i,s,0,-W[k]);
        add(s,i,INF,W[t1+1]);
        add(i,s,0,-W[t1+1]);
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
        ans+=tmpflow[t]*1LL*dis[t];
        //printf("%d %d\n",tmpflow[t],dis[t]);
    }
    printf("%lld\n",ans);
}
