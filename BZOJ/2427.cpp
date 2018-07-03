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

const int MAXN=110;
const int MAXM=2010;

int n,m;

namespace Tree{
    struct __edge{
        int nxt,v;
    }Edge[MAXM];
    int head[MAXN],cnt_e,v[MAXN];
    int w[MAXN],f[MAXN][510];
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
    void dfs(int x,int fa)
    {
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(v==fa) continue;
            dfs(v,x);
            for(int j=m-w[x];j>=0;j--)
                for(int k=0;k<=j;k++)
                    f[x][j]=max(f[x][j],f[x][k]+f[v][j-k]);
        }
        for(int i=m;i>=0;i--)
            if(i>=w[x]) f[x][i]=f[x][i-w[x]]+v[x];
            else f[x][i]=0;
    }
}

namespace Graph{
    struct __edge{
        int nxt,v;
    }Edge[MAXM];
    int head[MAXN],cnt_e,dfn[MAXN],low[MAXN],SCC[MAXN],cnt,dft;
    int stk[MAXN],top,v[MAXN],w[MAXN],SCC_v[MAXN],SCC_w[MAXN],in[MAXN];
    bool ins[MAXN];
    set<int> T[MAXN];
    vector<int> pnt[MAXN];
    inline void add(int u,int v)
    {
        Edge[++cnt_e].v=v;
        Edge[cnt_e].nxt=head[u];
        head[u]=cnt_e;
    }
    void tarjan(int x)
    {
        dfn[x]=low[x]=++dft;
        stk[++top]=x;ins[x]=1;
        for(int i=head[x];i;i=Edge[i].nxt)
        {
            int v=Edge[i].v;
            if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
            else if(ins[v]) low[x]=min(low[x],dfn[v]);
        }
        if(low[x]==dfn[x])
        {
            ++cnt;
            while(top&&stk[top]!=x)
            {
                SCC[stk[top]]=cnt;
                ins[stk[top]]=0;
                SCC_v[cnt]+=v[stk[top]];
                SCC_w[cnt]+=w[stk[top]];
                pnt[cnt].push_back(stk[top]);
                top--;
            }
            assert(x==stk[top]);
            pnt[cnt].push_back(x);
            SCC_v[cnt]+=v[x];
            SCC_w[cnt]+=w[x];
            SCC[x]=cnt;
            ins[x]=0;
            top--;
        }
    }
    void build_tree()
    {
        for(int i=1;i<=n;i++)
            if(!dfn[i]) tarjan(i);
        for(int i=1;i<=cnt;i++)
        {
            for(int j=0;j<pnt[i].size();j++)
            {
                int x=pnt[i][j];
                for(int l=head[x];l;l=Edge[l].nxt)
                    if(SCC[Edge[l].v]!=i)
                        T[i].insert(SCC[Edge[l].v]);
            }
            for(set<int>::iterator it=T[i].begin();it!=T[i].end();++it)
                Tree::add(i,*it),++in[*it];
            Tree::v[i]=SCC_v[i];Tree::w[i]=SCC_w[i];
        }
        for(int i=1;i<=cnt;i++) if(!in[i]) Tree::add(0,i);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&Graph::w[i]);
    for(int i=1;i<=n;i++) scanf("%d",&Graph::v[i]);
    for(int i=1,v;i<=n;i++) scanf("%d",&v),v?Graph::add(v,i):void();
    Graph::build_tree();
    Tree::dfs(0,-1);
    printf("%d\n",Tree::f[0][m]);
    #ifdef LOCAL
        system("pause");
    #endif
}