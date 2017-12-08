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
const int MAXN=200010;
const int MAXM=200010;
int head[MAXN];
struct Node{
    int flow,nxt,v,u;
}Edge[MAXM];
int cnte=1;  //notice
inline void add(const int &u,const int &v,const int &val1,const int &val2)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].u=u;
    Edge[cnte].v=v;
    Edge[cnte].flow=val1;
    head[u]=cnte;
    Edge[++cnte].nxt=head[v];
    Edge[cnte].v=u;
    Edge[cnte].flow=val2;
    head[v]=cnte;
}
int s,t=300,n,m,t1,t2,ans;
int lvl[302];
bool bfs()
{
    queue<int> q;
    q.push(s);
    memset(lvl,0,sizeof(lvl));
    lvl[s]=1;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
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
    for(int i=head[x];i&&cur_flow>add_flow;i=Edge[i].nxt)
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
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
        add(s,i,1,0);
    for(int i=m+1;i<=m+n;i++)
        add(i,t,1,0);
    int tp=cnte;
    while(scanf("%d%d",&t1,&t2)&&t1!=-1&&t2!=-1)
        add(t1,t2,1,0);
    while(bfs())
        ans+=dfs(s,1<<30);
    printf("%d\n",ans);
    for(int i=tp+1;i<=cnte;i++)
    {
        if(!i%1)
            continue;
        if(!Edge[i].flow&&Edge[i].u!=s&&Edge[i].v!=t&&Edge[i].v!=s&&Edge[i].v!=t)
            printf("%d %d\n",Edge[i].u,Edge[i].v);
    }
}
