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
#define MAXM 200010
#define MAXN 500
const int INF=0x3f3f3f3f;
int head[MAXN];
struct Node{
    int flow,nxt,v;
}Edge[MAXM];
int cnte=1,n,lvl[MAXN],s,t;
int ats[MAXN],thome[MAXN];
inline void add(const int &u,const int &v,const int &val)
{
    //printf("u:%d v:%d val:%d\n",u,v,val);
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}
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
    if(x==t) return cur_flow;
    int add_flow=0;
    for(int i=head[x];i&&add_flow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(lvl[v]!=lvl[x]+1||!Edge[i].flow)
            continue;
        int min_flow=dfs(v,min(Edge[i].flow,cur_flow-add_flow));
        Edge[i].flow-=min_flow;
        Edge[i^1].flow+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int main()
{
    int T,tmp;
    s=0,t=400;
    scanf("%d",&T);
    while(T--)
    {
        int ans=0,cnt=0;
        cnte=1;
        memset(Edge,0,sizeof(Edge));
        memset(head,0,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&ats[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&thome[i]);
        for(int i=1;i<=n;i++)
            if(ats[i]&&!thome[i])
                cnt++,
                add(s,i,1),
                add(i,s,0);
            else if(!ats[i])
                cnt++,
                add(s,i,1),
                add(i,s,0);
        for(int i=1;i<=n;i++)
            if(ats[i])
                add(i+200,t,1),
                add(t,i+200,0);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                scanf("%d",&tmp);
                if(i==j&&ats[i])
                    add(i,i+200,1),
                    add(i+200,i,0);
                if(!tmp)
                    continue;
                add(i,j+200,1),
                add(j+200,i,0);
            }
        while(bfs())
            ans+=dfs(s,INF);
        if(ans==cnt)
            putchar(94),putchar(95),putchar(94),putchar('\n');
        else puts("T_T");
    }
}
