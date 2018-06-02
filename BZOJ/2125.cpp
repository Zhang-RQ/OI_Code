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
const int MAXN=10010;
const int INF=0x3f3f3f3f;
map<int,int> f[MAXN]; //记录边权
map<int,int> dist[MAXN];//记录环i上根到某个点的距离
vector<int> rings[MAXN],bl[MAXN];// 分别记录环i所包含的点,点i是那些环的根
int cnt,dfn[MAXN],low[MAXN],dft,stk[MAXN],top,n,siz[MAXN],dis[MAXN],m,q;
inline void add(int u,int v,int w)
{
    if(f[u].find(v)==f[u].end()) f[u][v]=INF;
    f[u][v]=min(f[u][v],w);
}
namespace Tree{
    int fa[MAXN<<1][16],dep[MAXN<<1]; //1--n 方点
    pair<int,int> _lca;
    int get_dep(int x)
    {
        if(!fa[x][0]) dep[x]=1;
        if(dep[x]) return dep[x];
        else return dep[x]=get_dep(fa[x][0])+1;
    }
    void init()
    {
        for(int j=1;j<=15;j++)
        {
            for(int i=1;i<=cnt;i++)
                fa[i][j]=fa[fa[i][j-1]][j-1];
            for(int i=n+1;i<=n<<1;i++)
                fa[i][j]=fa[fa[i][j-1]][j-1];
        }
        for(int i=1;i<=cnt;i++)
            get_dep(i);
        for(int i=n+1;i<=n<<1;i++)
            get_dep(i);
    }
    int LCA(int x,int y)
    {
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=15;~i;i--)
            if(dep[fa[x][i]]>=dep[y])
                x=fa[x][i];
        if(x==y) return x;
        for(int i=15;~i;i--)
            if(fa[x][i]!=fa[y][i])
                x=fa[x][i],y=fa[y][i];
        _lca=make_pair(x,y);
        return fa[x][0];
    }
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dft;stk[++top]=x;
    map<int,int>::iterator it;
    for(it=f[x].begin();it!=f[x].end();++it)
    {
        if(dfn[it->first]) low[x]=min(low[x],dfn[it->first]);
        else
        {
            tarjan(it->first);
            if(dfn[x]==low[it->first])
            {
                rings[++cnt].push_back(x);
                bl[x].push_back(cnt);
                Tree::fa[cnt][0]=n+x;
                int t;
                do{
                    t=stk[top--];
                    rings[cnt].push_back(t);
                    Tree::fa[t+n][0]=cnt;
                }while(t!=it->first);
            }
            low[x]=min(low[x],low[it->first]);
        }
    }
}
void dfs(int x) //dfs x 这个环
{
    top=0;
    vector<int>::iterator it,_it;
    for(it=rings[x].begin();it!=rings[x].end();++it)
        stk[++top]=*it;
    stk[++top]=*rings[x].begin();
    for(int i=1;i<top;i++)
    {
        siz[x]+=f[stk[i]][stk[i+1]];
        if(i!=top-1) dist[x][stk[i+1]]=dist[x][stk[i]]+f[stk[i]][stk[i+1]];
    }
    int i=2,j=top-1;
    while(i<=j)
    {
        if(dis[stk[i-1]]+f[stk[i-1]][stk[i]]<dis[stk[j+1]]+f[stk[j+1]][stk[j]])
            dis[stk[i]]=dis[stk[i-1]]+f[stk[i-1]][stk[i]],i++;
        else 
            dis[stk[j]]=dis[stk[j+1]]+f[stk[j+1]][stk[j]],j--;
    }
    for(it=rings[x].begin(),++it;it!=rings[x].end();++it)
        for(_it=bl[*it].begin();_it!=bl[*it].end();++_it)
            dfs(*_it);
}
int main()
{
    using namespace Tree;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    tarjan(1);init();
    for(vector<int>::iterator it=bl[1].begin();it!=bl[1].end();++it) dfs(*it);
    for(int i=1,u,v;i<=q;i++)
    {
        scanf("%d%d",&u,&v);
        int lca=LCA(n+u,n+v);
        if(lca>n) printf("%d\n",dis[u]+dis[v]-2*dis[lca-n]);
        else
        {
            int ans=dis[u]+dis[v]-dis[_lca.first-n]-dis[_lca.second-n];
            int tmp=abs(dist[lca][_lca.first-n]-dist[lca][_lca.second-n]);
            ans+=min(tmp,siz[lca]-tmp);
            printf("%d\n",ans);
        }
    }
    #ifdef LOCAL
        system("pause");
    #endif
}