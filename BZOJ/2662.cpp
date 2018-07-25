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
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;
using namespace std;

const int MAXN=51;
const int MAXK=51;
const int MAXM=1010;

struct __edge{
    int nxt,v,w;
}Edge[MAXM<<1];

bool vis[MAXN][MAXK];
int dis[MAXN][MAXK],n,m,k;
int head[MAXN],cnt_e;

inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}

struct node{
    int x,d,t;
    node(){}
    node(int _,int __,int ___){x=_;d=__;t=___;}
    bool operator < (const node &rhs) const {return d>rhs.d||(d==rhs.d&&t>rhs.t);}
};

priority_queue<node> pq;

void dijsktra()
{
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[1][0]=0;
    pq.push(node(1,0,0));
    while(!pq.empty())
    {
        node t=pq.top();pq.pop();
        if(vis[t.x][t.t]) continue;
        vis[t.x][t.t]=1;
        for(int i=head[t.x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(dis[t.x][t.t]+Edge[i].w<dis[v][t.t])
                dis[v][t.t]=dis[t.x][t.t]+Edge[i].w,pq.push(node(v,dis[v][t.t],t.t));
            if(t.t<k&&(dis[t.x][t.t]+(Edge[i].w>>1))<dis[v][t.t+1])
                dis[v][t.t+1]=dis[t.x][t.t]+(Edge[i].w>>1),pq.push(node(v,dis[v][t.t+1],t.t+1));
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,u,v,w;i<=m;i++)
        scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
    dijsktra();
    int ans=0x3f3f3f3f;
    for(int i=0;i<=k;i++) ans=min(ans,dis[n][i]);
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}