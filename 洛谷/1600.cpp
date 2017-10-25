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
int n,m,u,v;
#define MAXM 300010
#define MAXN 300010
int head[MAXN];
struct node{
    int v,nxt;
}Edge[MAXN<<1];
int cnte=0;
inline void add(int u,int v)
{
    Edge[++cnte].nxt=head[u];
    Edge[cnte].v=v;
    head[u]=cnte;
}
int st[MAXN<<1][20],lca[MAXN<<1][20],pos[MAXN],dep[MAXN],fa[MAXN],lg2[MAXN<<1],w[MAXN];
int cnt=0,maxdep=0;
void dfs(int x,int father)
{
    fa[x]=father;
    st[pos[x]=++cnt][0]=dep[x]=dep[father]+1;
    lca[pos[x]][0]=x;
    maxdep=max(maxdep,dep[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        dfs(v,x);
        st[++cnt][0]=dep[x];
        lca[cnt][0]=x;
    }
}
void work()
{
    for(int i=2;i<=cnt;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[cnt];j++)
        for(int i=1;i+(1<<j)-1<=cnt;i++)
            if(st[i][j-1]<=st[i+(1<<(j-1))][j-1])
                st[i][j]=st[i][j-1],
                lca[i][j]=lca[i][j-1];
            else
                st[i][j]=st[i+(1<<(j-1))][j-1],
                lca[i][j]=lca[i+(1<<(j-1))][j-1];
}
int get_lca(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    if(st[x][len]<=st[y-(1<<len)+1][len])
        return lca[x][len];
    else return lca[y-(1<<len)+1][len];
}
struct Node{
    int u,v,dis,lca;
}path[MAXM];
int Stag[MAXN];
vector<int> lcatag[MAXN],Ttag[MAXN];
int bucket[MAXN<<1],ans[MAXN];
void DFS_UP(int x)
{
    int val=dep[x]+w[x],lastbucket=0;
    if(val<=maxdep) lastbucket=bucket[val];
    for(int i=head[x],v=Edge[i].v;i;i=Edge[i].nxt,v=Edge[i].v) if(v!=fa[x]) DFS_UP(v);
    bucket[dep[x]]+=Stag[x];
    if(val<=maxdep) ans[x]+=bucket[val]-lastbucket;
    int siz=lcatag[x].size();
    for(int i=0;i<siz;i++) --bucket[lcatag[x][i]];
}
void DFS_DOWN(int x)
{
    int val=w[x]-dep[x]+MAXN,lastbucket=bucket[val];
    for(int i=head[x],v=Edge[i].v;i;i=Edge[i].nxt,v=Edge[i].v) if(v!=fa[x]) DFS_DOWN(v);
    int siz=Ttag[x].size();
    for(int i=0;i<siz;i++) ++bucket[Ttag[x][i]];
    ans[x]+=bucket[val]-lastbucket;
    siz=lcatag[x].size();
    for(int i=0;i<siz;i++) --bucket[lcatag[x][i]];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    work();
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&path[i].u,&path[i].v);
        path[i].lca=get_lca(path[i].u,path[i].v);
        path[i].dis=dep[path[i].u]+dep[path[i].v]-2*dep[path[i].lca];
    }
    for(int i=1;i<=m;i++)
    {
        Stag[path[i].u]++;
        lcatag[path[i].lca].push_back(dep[path[i].u]);
    }
    DFS_UP(1);
    memset(bucket,0,sizeof(bucket));
    for(int i=1;i<=n;i++) lcatag[i].clear();
    for(int i=1; i<=m; i++)
    {
        Ttag[path[i].v].push_back(path[i].dis-dep[path[i].v]+MAXM);
        lcatag[path[i].lca].push_back(path[i].dis-dep[path[i].v]+MAXM);
    }
    DFS_DOWN(1);
    for(int i=1; i<=m; i++)
        if(w[path[i].lca]+dep[path[i].lca]==dep[path[i].u]) ans[path[i].lca]--;
    printf("%d",ans[1]);
    for(int i=2;i<=n;i++) printf(" %d",ans[i]);
    puts("");
    return 0;
}
