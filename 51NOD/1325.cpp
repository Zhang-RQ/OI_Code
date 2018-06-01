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
const int MAXN=1E3+10;
const int MAXM=1E4+10;
const int INF=1<<30;
namespace Network_flow{
    struct __edge{
        int nxt,v,f;
    }Edge[MAXM];
    int head[MAXN],cnt_e=1,S,T=MAXN-1,lvl[MAXN];
    inline void add(int u,int v,int f)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        Edge[cnt_e].f=f;
        head[u]=cnt_e;
    }
    bool bfs()
    {
        memset(lvl,0,sizeof lvl);
        queue<int> q;
        q.push(S);lvl[S]=1;
        while(!q.empty())
        {
            int x=q.front();q.pop();
            for(int i=head[x];i;i=Edge[i].nxt)
            {
                int v=Edge[i].v;
                if(lvl[v]||!Edge[i].f) continue;
                lvl[v]=lvl[x]+1;q.push(v);
            }
        }
        return lvl[T]!=0;
    }
    int dfs(int x,int cur)
    {
        if(x==T) return cur;
        int add_flow=0;
        for(int i=head[x];i&&cur>add_flow;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!Edge[i].f||lvl[v]!=lvl[x]+1) continue;
            int min_flow=dfs(v,min(cur-add_flow,Edge[i].f));
            if(!min_flow) lvl[v]=0;
            add_flow+=min_flow;
            Edge[i].f-=min_flow;
            Edge[i^1].f+=min_flow;
        }
        return add_flow;
    }
    int MaxFlow()
    {
        int ret=0;
        while(bfs()) ret+=dfs(S,INF);
        return ret;
    }
}
using namespace Network_flow;
struct Tre{
    struct __edge{
        int nxt,v;
    }Edge[MAXM];
    int head[MAXN],cnt_e;
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
}Tree[2];
int val[MAXN],n,rt;
void dfs(int x,int fa,int t)
{
    if(fa) add(x,fa,INF),add(fa,x,0);
    for(int i=Tree[t].head[x];i;i=Tree[t].Edge[i].nxt)
        if(Tree[t].Edge[i].v!=fa)
            dfs(Tree[t].Edge[i].v,x,t);
}
int solve()
{
    memset(head,0,sizeof head);cnt_e=1;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(i==rt) {ans+=val[i];add(S,i,INF),add(i,S,0);continue;}
        if(val[i]>0) ans+=val[i],add(S,i,val[i]),add(i,S,0);
        else add(i,T,-val[i]),add(T,i,0);
    }
    dfs(rt,0,0);dfs(rt,0,1);
    return ans-MaxFlow();
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    for(int i=0,u,v;i<=1;i++)
        for(int j=1;j<n;j++)
            scanf("%d%d",&u,&v),++u,++v,Tree[i].add(u,v),Tree[i].add(v,u);
    int ans=0;
    for(rt=1;rt<=n;rt++) ans=max(ans,solve());
    printf("%d\n",ans);
    #ifdef LOCAL
        system("pause");
    #endif
}