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
const int MAXM=2E5+5;

struct __edge{
    int nxt,v;
}Edge[MAXM];

struct nd{
    int son[2],v;
}t[MAXN<<8];

int head[MAXN],cnt_e,val[MAXN],q,siz[MAXN];
int dfn[MAXN],dfnt,rt1[MAXN],rt2[MAXN],fa[MAXN],rdfn[MAXN];
int cnt,n,pos[MAXN],st[MAXN<<1][21],lca[MAXN<<1][21],lg2[MAXN<<1],dft,dep[MAXN];

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

inline void insert(int x,int y,int val)
{
    bool v;
    for(int i=30;~i;i--)
    {
        t[x]=t[y];t[x].v++;
        v=(val>>i)&1;
        t[x].son[v]=++cnt;
        x=t[x].son[v];y=t[y].son[v];
    }
    t[x]=t[y];t[x].v++;
}

inline int query(int x,int y,int val)
{
    int ret=0,v;
    for(int i=30;~i;i--)
    {
        v=((val>>i)&1)^1;
        if(t[t[x].son[v]].v-t[t[y].son[v]].v) ret|=v<<i,x=t[x].son[v],y=t[y].son[v];
        else ret|=(v^1)<<i,x=t[x].son[v^1],y=t[y].son[v^1];
    }
    return ret^val;
}

inline int query(int x,int y,int z,int val)
{
    int ret=0,v;
    for(int i=30;~i;i--)
    {
        v=((val>>i)&1)^1;
        if(t[t[x].son[v]].v+t[t[y].son[v]].v-2*t[t[z].son[v]].v) ret|=v<<i,x=t[x].son[v],y=t[y].son[v],z=t[z].son[v];
        else ret|=(v^1)<<i,x=t[x].son[v^1],y=t[y].son[v^1],z=t[z].son[v^1];
    }
    return ret^val;
}

void dfs(int x,int fa)
{
    st[pos[x]=++dft][0]=dep[x];
    lca[dft][0]=x;dfn[x]=++dfnt;
    rdfn[dfn[x]]=x;
    insert(rt2[x]=++cnt,rt2[fa],val[x]);
    ::fa[x]=fa;siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dep[v]=dep[x]+1;
        dfs(v,x);siz[x]+=siz[v];
        st[++dft][0]=dep[x];
        lca[dft][0]=x;
    }
}

void init()
{
    for(int i=2;i<=dft;i++)
        lg2[i]=lg2[i>>1]+1;
    for(int j=1;j<=lg2[dft];j++)
        for(int i=1;i+(1<<(j-1))<=dft;i++)
            st[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?st[i][j-1]:st[i+(1<<(j-1))][j-1],
            lca[i][j]=st[i][j-1]<st[i+(1<<(j-1))][j-1]?lca[i][j-1]:lca[i+(1<<(j-1))][j-1];
}

int get_lca(int x,int y)
{
    x=pos[x];y=pos[y];
    if(x>y) swap(x,y);
    int len=lg2[y-x+1];
    return st[x][len]<st[y-(1<<len)+1][len]?lca[x][len]:lca[y-(1<<len)+1][len];
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(1,0);init();
    for(int i=1;i<=n;i++) insert(rt1[i]=++cnt,rt1[i-1],val[rdfn[i]]);
    for(int i=1,x,y,v,opt;i<=q;i++)
    {
        scanf("%d",&opt);
        if(opt==1) scanf("%d%d",&x,&v),printf("%d\n",query(rt1[dfn[x]+siz[x]-1],rt1[dfn[x]-1],v));
        else scanf("%d%d%d",&x,&y,&v),printf("%d\n",query(rt2[x],rt2[y],rt2[fa[get_lca(x,y)]],v));
    }
    #ifdef LOCAL
        system("pause");
    #endif
}