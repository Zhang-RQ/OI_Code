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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=1010;
const int MAXM=20100;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int T,n,m,s,t,u,v,w;
int dis[2][MAXN],cnt[2][MAXN];
bool vis[MAXN];
struct cmp{
    bool operator () (int a,int b)
    {
        if(dis[0][a]!=dis[0][b]) return dis[0][a]>dis[0][b];
        else return dis[1][a]>dis[1][b];
    }
};
void dijkstra()
{
    priority_queue<int,vector<int>,cmp> q;
    memset(dis,0x3f,sizeof(dis));
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    dis[0][s]=0;
    cnt[0][s]=1;
    q.push(s);
    while(!q.empty())
    {
        int x=q.top();
        q.pop();
        if(!vis[x])
        {
            vis[x]=1;
            for(int i=head[x];i;i=Edge[i].nxt)
            {
                int v=Edge[i].v;
                for(int k=0;k<=1;k++)
                {
                    int tdis=dis[k][x]+Edge[i].w;
                    if(dis[0][v]==tdis)
                        cnt[0][v]+=cnt[k][x];
                    if(dis[1][v]==tdis)
                        cnt[1][v]+=cnt[k][x];
                    if(tdis<dis[0][v])
                    {
                        dis[1][v]=dis[0][v];
                        cnt[1][v]=cnt[0][v];
                        dis[0][v]=tdis;
                        cnt[0][v]=cnt[k][x];
                        q.push(v);
                    }
                    if(dis[0][v]<tdis&&tdis<dis[1][v])
                    {
                        dis[1][v]=tdis;
                        cnt[1][v]=cnt[k][x];
                        q.push(v);
                    }
                }
            }
        }
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cnt_e=0;
        memset(head,0,sizeof(head));
        memset(&Edge,0,sizeof(Edge));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
        }
        scanf("%d%d",&s,&t);
        dijkstra();
        int ans=cnt[0][t];
        if(dis[1][t]==dis[0][t]+1) ans+=cnt[1][t];
        printf("%d\n",ans);
    }
}
