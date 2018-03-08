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
const int MAXN=1E5+10;
const int MAXM=4E5+10;
const int INF=0x3f3f3f3f;
struct node{
    int nxt,u,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
int val[51][51][51],P,Q,R,D;
inline int id(int x,int y,int z) {return x+y*40+z*1600;}
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    Edge[cnt_e].u=u;
    head[u]=cnt_e;
}
int lvl[MAXN],n,m;
const int s=0,t=MAXN-1;
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
int dfs(int x,int flow)
{
    if(x==t) return flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].w)
            continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        if(!min_flow) lvl[v]=0;
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    scanf("%d%d%d",&P,&Q,&R);
    scanf("%d",&D);
    for(int k=1;k<=R;k++)
        for(int i=1;i<=P;i++)
            for(int j=1;j<=Q;j++)
                scanf("%d",&val[i][j][k]),add(id(i,j,k),id(i,j,k+1),val[i][j][k]),add(id(i,j,k+1),id(i,j,k),0);
    for(int i=1;i<=P;i++)
        for(int j=1;j<=Q;j++)
            add(s,id(i,j,1),INF),add(id(i,j,1),s,0),
            add(id(i,j,R+1),t,INF),add(t,id(i,j,R+1),0);
    for(int i=1;i<=P;i++)
        for(int j=1;j<=Q;j++)
        {
            if(i!=1)
                for(int k=D+1;k<=R+1;k++)
                    add(id(i,j,k),id(i-1,j,k-D),INF),add(id(i-1,j,k-D),id(i,j,k),0);
            if(i!=P)
                for(int k=D+1;k<=R+1;k++)
                    add(id(i,j,k),id(i+1,j,k-D),INF),add(id(i+1,j,k-D),id(i,j,k),0);
            if(j!=Q)
                for(int k=D+1;k<=R+1;k++)
                    add(id(i,j,k),id(i,j+1,k-D),INF),add(id(i,j+1,k-D),id(i,j,k),0);
            if(j!=1)
                for(int k=D+1;k<=R+1;k++)
                    add(id(i,j,k),id(i,j-1,k-D),INF),add(id(i,j-1,k-D),id(i,j,k),0);
        }
    int ans=0;
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
