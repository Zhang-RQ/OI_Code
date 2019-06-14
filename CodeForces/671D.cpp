#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3E5+10;

int n,m,rt[MAXN],dep[MAXN],cnt,lef[MAXN],jmp[MAXN][19];
vector<pair<ll,int> > lk[MAXN];
vector<int> g[MAXN],T[MAXN];
vector<ll> pre[MAXN],suf[MAXN];

struct node_t{
    pair<ll,int> v;
    int l,r,h;
    ll add;
}t[MAXN];

void pushdown(int x)
{
    if(t[x].add)
    {
        t[t[x].l].v.first+=t[x].add;
        t[t[x].r].v.first+=t[x].add;
        t[t[x].l].add+=t[x].add;
        t[t[x].r].add+=t[x].add;
        t[x].add=0;
    }
}

int merge(int x,int y)
{
    if(!x||!y) return x|y;
    pushdown(x);pushdown(y);
    if(t[x].v>t[y].v) swap(x,y);
    t[x].r=merge(t[x].r,y);
    if(t[t[x].l].h<t[t[x].r].h) swap(t[x].l,t[x].r);
    t[x].h=t[t[x].r].h+1;
    return x;
}

int Nxt(int x,int y)
{
    for(int j=18;~j;j--)
        if(dep[jmp[x][j]]>dep[y])
            x=jmp[x][j];
    return x;
}

void dfs1(int x,int fa)
{
    dep[x]=dep[fa]+1;
    jmp[x][0]=fa;
    for(int v:g[x])
        if(v!=fa)
            T[x].push_back(v),dfs1(v,x);
}

void dfs(int x)
{
    for(int v:T[x])
        dfs(v);
    pre[x].resize(T[x].size());
    suf[x].resize(T[x].size());
    for(int _=0;_<(int)T[x].size();_++)
    {
        int v=T[x][_];
        while(t[rt[v]].v.second>dep[x]+1) rt[v]=merge(t[rt[v]].l,t[rt[v]].r);
        pre[x][_]=(_?pre[x][_-1]:0)+t[rt[v]].v.first;
    }
    for(int _=T[x].size()-1;~_;--_)
    {
        int v=T[x][_];
        suf[x][_]=(_!=(int)T[x].size()-1?suf[x][_+1]:0)+t[rt[v]].v.first;
    }
    for(int _=0;_<(int)T[x].size();_++)
    {
        int v=T[x][_];
        t[rt[v]].add+=(_?pre[x][_-1]:0)+(_!=(int)T[x].size()-1?suf[x][_+1]:0);
        t[rt[v]].v.first+=(_?pre[x][_-1]:0)+(_!=(int)T[x].size()-1?suf[x][_+1]:0);
        rt[x]=merge(rt[x],rt[v]);
    }
    for(auto p:lk[x])
        t[++cnt].v=make_pair(p.first+(suf[x].size()?suf[x][0]:0),dep[p.second]),
        rt[x]=merge(rt[x],cnt);
    if(!rt[x]) throw -1;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    dfs1(1,0);
    for(int j=1;j<=18;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        if(u==v) continue;
        v=Nxt(u,v);
        lk[u].emplace_back(w,v);
    }
    lk[1].emplace_back(0,1);
    try{
        dfs(1);
    }catch(int error){
        puts("-1");
        return 0;
    }
    printf("%lld\n",t[rt[1]].v.first);
}
