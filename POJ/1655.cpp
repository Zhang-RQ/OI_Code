#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
struct Node{
    int v,nxt;
}Edge[40100];
bool vis[20100];
int fa[20100];
int Adj[20100];
int d[20100];
int cnt=0;
int num=0;
int ansn,ans=0x3f3f3f3f;
void add(int u,int v)
{
    Edge[++cnt].nxt=Adj[u];
    Edge[cnt].v=v;
    Adj[u]=cnt;
    Edge[++cnt].nxt=Adj[v];
    Edge[cnt].v=u;
    Adj[v]=cnt;
}
void dfs(int x)
{
    int maxsub=0;
    vis[x]=1;
    d[x]=1;
    if(Adj[x])     for(int i=Adj[x];i;i=Edge[i].nxt)
    {
        if(vis[Edge[i].v])      continue;
        dfs(Edge[i].v);
        d[x]+=d[Edge[i].v];
        maxsub=max(maxsub,d[Edge[i].v]);
    }
    maxsub=max(maxsub,num-d[x]);
    if(maxsub<ans)
    {
        ans=maxsub;
        ansn=x;
    }
}
int main()
{
    int T,m;
    int u,v;
    scanf("%d",&T);
    while(T--)
    {
        memset(Adj,0,sizeof(Adj));
        memset(Edge,0,sizeof(Edge));
        cnt=0;
        scanf("%d",&m);
        for(int i=1;i<=m-1;i++)   scanf("%d%d",&u,&v),add(u,v);
        num=m;
        dfs(1);
        //for(int i=1;i<=m;i++)   printf("%d\n",d[i]);
        printf("%d %d\n",ansn,ans);
    }
}
