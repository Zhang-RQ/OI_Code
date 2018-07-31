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

const int MAXN=1E5+5;
const int MAXM=1E6+5;

struct Graph{
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
}Gr,G;

int dfn[MAXN],n,m,low[MAXN],cnt,bl[MAXN],SCC,stk[MAXN],top,siz[MAXN],P;
int dis[MAXN],f[MAXN],in[MAXN],lst[MAXN];
bool ins[MAXN];
queue<int> q;

void tarjan(int x)
{
    low[x]=dfn[x]=++cnt;
    stk[++top]=x;ins[x]=1;
    for(int i=Gr.head[x];i;i=Gr.Edge[i].nxt)
    {
        int v=Gr.Edge[i].v;
        if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if(ins[v]) low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x])
    {
        ++SCC;siz[SCC]=1;
        while(stk[top]!=x)
        {
            bl[stk[top]]=SCC;
            ins[stk[top]]=0;
            ++siz[SCC];
            --top;
        }
        ins[x]=0;bl[x]=SCC;
        --top;
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&P);
    for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v),Gr.add(u,v);
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        for(int j=Gr.head[i];j;j=Gr.Edge[j].nxt)
            if(bl[i]!=bl[Gr.Edge[j].v])
                G.add(bl[i],bl[Gr.Edge[j].v]),++in[bl[Gr.Edge[j].v]];
    for(int i=1;i<=SCC;i++) if(!in[i]) q.push(i),dis[i]=siz[i],f[i]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        for(int i=G.head[x];i;i=G.Edge[i].nxt)
        {
            int v=G.Edge[i].v;
            if(!(--in[v])) q.push(v);
            if(x==lst[v]) continue;
            if(dis[v]==dis[x]+siz[v]) (f[v]+=f[x])%=P;
            if(dis[v]<dis[x]+siz[v])  dis[v]=dis[x]+siz[v],f[v]=f[x];
            lst[v]=x;
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=SCC;i++) ans1=max(ans1,dis[i]);
    for(int i=1;i<=SCC;i++) if(dis[i]==ans1) (ans2+=f[i])%=P;
    printf("%d\n%d\n",ans1,ans2);
    #ifdef LOCAL
        system("pause");
    #endif
}