#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXM=3E5+10;

struct edge_t{
    int u,v,w;

    bool operator < (const edge_t &rhs) const {return w<rhs.w;}
}Edge[MAXM],nEdge[MAXM],Edge2[450],Edge3[40];

int G[25][25];
int n,m,k,fa[MAXN],np,cnte,cnt2,cnt3,bl[MAXN];
int Ue[30],Ve[30],Mn[30][30],fa1[30],dep[30];
ll p[MAXN],sp[30],f[30];
vector<int> T[MAXN];
set<int> S;

void chmin(int &x,int y){if(y<x) x=y;}

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;
    fa1[x]=fa;
    f[x]=sp[x];
    for(int v:T[x])
        if(v!=fa)
            dfs(v,x),
            f[x]+=f[v];
}

void cover(int x,int y,int w)
{
    if(dep[x]<dep[y])
        swap(x,y);
    while(dep[x]!=dep[y])
    {
        chmin(Mn[fa1[x]][x],w);
        chmin(Mn[x][fa1[x]],w);
        x=fa1[x];
    }
    while(x!=y)
    {
        chmin(Mn[fa1[x]][x],w);
        chmin(Mn[x][fa1[x]],w);
        chmin(Mn[fa1[y]][y],w);
        chmin(Mn[y][fa1[y]],w);
        x=fa1[x];y=fa1[y];
    }
}

ll solve(int S)
{
    memset(Mn,0x3f,sizeof Mn);
    for(int i=1;i<=np;i++)
        fa[i]=i,T[i].clear();
    for(int i=1;i<=k;i++)
        if((S>>(i-1))&1)
        {
            if(find(Ue[i])==find(Ve[i]))
                return 0;
            fa[find(Ue[i])]=find(Ve[i]);
            T[Ue[i]].push_back(Ve[i]);
            T[Ve[i]].push_back(Ue[i]);
        }
    for(int i=1;i<=cnt3;i++)
    {
        if(find(Edge3[i].u)==find(Edge3[i].v))
            continue;
        fa[find(Edge3[i].u)]=find(Edge3[i].v);
        T[Edge3[i].u].push_back(Edge3[i].v);
        T[Edge3[i].v].push_back(Edge3[i].u);
    }
    dfs(bl[1],0);
    for(int i=1;i<=cnt3;i++)
        cover(Edge3[i].u,Edge3[i].v,Edge3[i].w);
    ll Ans=0;
    for(int i=1;i<=k;i++)
        if((S>>(i-1))&1)
        {
            int x=dep[Ue[i]]>dep[Ve[i]]?Ue[i]:Ve[i];
            Ans+=1ll*f[x]*Mn[Ue[i]][Ve[i]];
        }
    return Ans;
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].w);
    for(int i=1;i<=k;i++)
        scanf("%d%d",&Ue[i],&Ve[i]);
    for(int i=1;i<=n;i++)
        scanf("%lld",&p[i]);
    sort(Edge+1,Edge+1+m);
    for(int i=1;i<=k;i++)
    {
        if(find(Ue[i])==find(Ve[i]))
            continue;
        fa[find(Ue[i])]=find(Ve[i]);
    }
    for(int i=1;i<=m;i++)
    {
        if(find(Edge[i].u)==find(Edge[i].v))
            continue;
        fa[find(Edge[i].u)]=find(Edge[i].v);
        nEdge[++cnte]=Edge[i];
    }
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=cnte;i++)
        fa[find(nEdge[i].u)]=find(nEdge[i].v);
    for(int i=1;i<=n;i++)
        if(find(i)==i)
            bl[i]=++np;
    for(int i=1;i<=n;i++)
    {
        if(find(i)!=i)
            bl[i]=bl[find(i)];
        sp[bl[i]]+=p[i];
    }
    memset(G,0x3f,sizeof G);
    for(int i=1;i<=m;i++)
    {
        int U=bl[Edge[i].u],V=bl[Edge[i].v];
        chmin(G[U][V],Edge[i].w);
        chmin(G[V][U],Edge[i].w);
    }
    for(int i=1;i<=np;i++)
        for(int j=i+1;j<=np;j++)
            if(G[i][j]<1E9)
                Edge2[++cnt2]=(edge_t){i,j,G[i][j]};
    sort(Edge2+1,Edge2+1+cnt2);
    for(int i=1;i<=np;i++)
        fa[i]=i;
    for(int i=1;i<=cnt2;i++)
    {
        if(find(Edge2[i].u)==find(Edge2[i].v))
            continue;
        Edge3[++cnt3]=Edge2[i];
        fa[find(Edge2[i].u)]=find(Edge2[i].v);
    }
    for(int i=1;i<=k;i++)
        Ue[i]=bl[Ue[i]],
        Ve[i]=bl[Ve[i]];
    ll Ans=0;
    for(int s=0;s<1<<k;s++)
        Ans=max(Ans,solve(s));
    printf("%lld\n",Ans);
}
