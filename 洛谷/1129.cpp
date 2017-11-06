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
int T,n,s=0,t=1000,tmp;
#define MAXM 200010
#define MAXN 1010
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM<<1];
int cnte=0;
inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
int lvl[MAXN];
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
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cnte=1;
        memset(head,0,sizeof(head));
        memset(Edge,0,sizeof(Edge));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&tmp);
                if(tmp)
                    add(i,j+500,1),
                    add(j+500,i,0);
            }
        for(int i=1;i<=n;i++)
            add(s,i,1),
            add(i,s,0),
            add(i+500,t,1),
            add(t,i+500,0);
        int ans=0;
        while(bfs())
            ans+=dfs(s,0x3f3f3f3f);
        if(ans!=n)
            puts("No");
        else puts("Yes");
    }
}
