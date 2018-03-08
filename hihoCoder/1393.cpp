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
const int MAXN=310;
const int MAXM=1E5+5;
struct node{
    int nxt,v,w;
}Edge[MAXM];
int head[MAXN],cnt_e=1;
inline void add(int u,int v,int w)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    Edge[cnt_e].w=w;
    head[u]=cnt_e;
}
int s=0,t=MAXN-1;
int lvl[MAXN];
bool bfs()
{
    memset(lvl,0,sizeof lvl);
    queue<int> q;
    q.push(s);lvl[s]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||!Edge[i].w) continue;
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
        if(lvl[v]!=lvl[x]+1||!Edge[i].w) continue;
        int min_flow=dfs(v,min(flow-add_flow,Edge[i].w));
        Edge[i].w-=min_flow;
        Edge[i^1].w+=min_flow;
        add_flow+=min_flow;
    }
    return add_flow;
}
int T,n,m,tot,tmp,tt,xx,ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(head,0,sizeof head);cnt_e=1;
        ans=tot=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&tmp),tot+=tmp,add(i+120,t,tmp),add(t,i+120,0);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&tt,&tmp);
            add(s,i,tt);add(i,s,0);
            for(int j=1;j<=tmp;j++)
            {
                scanf("%d",&xx);
                add(i,xx+120,1);
                add(xx+120,i,0);
            }
        }
        while(bfs())
            ans+=dfs(s,0x3f3f3f3f);
        puts(ans==tot?"Yes":"No");
    }
}
