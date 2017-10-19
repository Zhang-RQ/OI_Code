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
#define M 200010
#define N 200010
int head[M];
struct Node{
    int val,nxt,v;
}Edge[N<<1];
int cnte=0;
inline void add(int u,int v,int val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].val=val;
    head[u]=cnte;
}
int dis[N];
bool vis[N];
bool flag;
void DFS_SPFA(int x)
{
    if(flag) return;
    vis[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(dis[v]>dis[x]+Edge[i].val)
        {
            dis[v]=dis[x]+Edge[i].val;
            if(vis[v]) {flag=1;return;}
            else DFS_SPFA(v);
        }
    }
    vis[x]=0;
}
int main()
{
    int m,n,T,u,v,val;
    scanf("%d",&T);
    while(T--)
    {
        flag=0;
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        cnte=0;
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&val);
            add(u,v,val);
            if(val>=0) add(v,u,val);
        }
        for(int i=1;i<=n;i++)
        {
            DFS_SPFA(i);
            if(flag) break;
        }
        if(flag) puts("YE5");
        else puts("N0");
    }
}
