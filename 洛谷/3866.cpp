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
#define MAXM 101000
#define MAXN 2010
#define id(i,j) m*(i-1)+j
const int INF=0x3f3f3f3f;
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
int n,m,s=0,t=2001;
int mp[35][35],lvl[MAXN],ans=0;
bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    queue<int> q;
    q.push(s);lvl[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!Edge[i].flow||lvl[v])
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
        add_flow+=min_flow;
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
    }
    return add_flow;
}
inline bool ok(int x,int y)
{
    return 1<=x&&x<=n&&1<=y&&y<=m&&mp[x][y]!=-1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(mp[i][j]==-1)
                continue;
            if(i==1||i==n||j==1||j==m)
                add(id(i,j)+1000,t,INF,0);
            if(!mp[i][j])
                add(id(i,j),id(i,j)+1000,INF,0),add(s,id(i,j),INF,0);
            else
                add(id(i,j),id(i,j)+1000,mp[i][j],0);
            if(ok(i,j-1))
                add(id(i,j)+1000,id(i,j-1),INF,0);
            if(ok(i,j+1))
                add(id(i,j)+1000,id(i,j+1),INF,0);
            if(ok(i+1,j))
                add(id(i,j)+1000,id(i+1,j),INF,0);
            if(ok(i-1,j))
                add(id(i,j)+1000,id(i-1,j),INF,0);
        }
    }
    while(bfs())
        ans+=dfs(s,0x3f3f3f3f);
    printf("%d\n",ans);
}
