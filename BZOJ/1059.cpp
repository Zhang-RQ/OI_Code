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

const int MAXN=401;
const int MAXM=MAXN*MAXN;
const int INF=0x3f3f3f3f;

int head[MAXN],lvl[MAXN],_head[MAXN];

struct Node{
    int flow,nxt,v;
}Edge[MAXM];

int cnte=1;

inline void add(const int &u,const int &v,const int &val)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    Edge[cnte].flow=val;
    head[u]=cnte;
}

int n,m,s=0,t=MAXN-1,u,v,flow;

int dfs(int x,int cur_flow)
{
    if(x==t) return cur_flow;
    int addflow=0;
    for(int i=head[x];i&&addflow<cur_flow;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if((!Edge[i].flow)||lvl[v]!=lvl[x]+1) continue;
        int minflow=dfs(v,min(cur_flow-addflow,Edge[i].flow));
        Edge[i].flow-=minflow;
        Edge[i^1].flow+=minflow;
        addflow+=minflow;
    }
    return addflow;
}

bool bfs()
{
    memset(lvl,0,sizeof(lvl));
    queue<int> q;
    q.push(s);
    lvl[s]=1;
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        for(int i=head[tmp];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(lvl[v]||(!Edge[i].flow)) continue;
            lvl[v]=lvl[tmp]+1;
            q.push(v);
        }
    }
    return lvl[t]!=0;
}

void solve()
{
    memset(head,0,sizeof head);
    cnte=1;
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&x);
            if(x) add(i,j+n,1),add(j+n,i,0);
        }
    for(int i=1;i<=n;i++) add(s,i,1),add(i,s,0),add(t,i+n,0),add(i+n,t,1);
    int ans=0;
    while(bfs()) ans+=dfs(s,INF);
    puts(ans==n?"Yes":"No");
}

int main()
{
    int T;
    for(scanf("%d",&T);T--;solve());
    #ifdef LOCAL
        system("pause");
    #endif
}