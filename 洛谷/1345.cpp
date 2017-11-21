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
const int MAXN=310;
const int MAXM=200010;
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
int lvl[MAXN];
int s,t,n,m,t1,t2;
bool bfs()
{
    queue<int> q;
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;q.push(s);
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
    if(x==t) return cur_flow;
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
    scanf("%d%d%d%d",&n,&m,&s,&t);//i入点   i+150 出点
    s+=150;
    for(int i=1;i<=m;i++)
        scanf("%d%d",&t1,&t2),
        add(t1,t2+150,0,INF),
        add(t2,t1+150,0,INF);
    for(int i=1;i<=n;i++)
        add(i,i+150,1,0);
    while(bfs())
        ans+=dfs(s,INF);
    printf("%d\n",ans);
}
