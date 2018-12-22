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

#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=100010;
const int MAXM=200010;

struct __edge{
    int nxt,v;
}Edge[MAXM<<1];

set<int> g[MAXN];
int n,m,head[MAXN],cnt_e,t[MAXN<<2],tg[MAXN<<2],pos[MAXN],siz[MAXN],son[MAXN],top[MAXN],fa[MAXN],dft;
int Fa[MAXN],cntQ,dep[MAXN],Tp[MAXM],cnt;
pair<int,int> Q[MAXM];
vector<int> ng[MAXN];
stack<int> stk;

int find(int x){return x==Fa[x]?x:Fa[x]=find(Fa[x]);}

inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}

void pushup(int x){t[x]=t[x<<1]+t[x<<1|1];}

void pushdown(int x)
{
    if(tg[x])
    {
        tg[x]=t[x<<1]=t[x<<1|1]=0;    
        tg[x<<1]=tg[x<<1|1]=1;
    }
}

void build(int x,int l,int r)
{
    if(l==r) return t[x]=1,void();
    int mid=(l+r)>>1;
    build(x<<1,l,mid);build(x<<1|1,mid+1,r);
    pushup(x);
}

void change(int x,int l,int r,int cl,int cr)
{
    if(!t[x]) return;
    if(cl<=l&&r<=cr) return t[x]=0,tg[x]=1,void();
    int mid=(l+r)>>1;pushdown(x);
    if(cl<=mid) change(x<<1,l,mid,cl,cr);
    if(cr>mid)  change(x<<1|1,mid+1,r,cl,cr);
    pushup(x);
}

int query(int x,int l,int r,int ql,int qr)
{
    if(!t[x]) return 0;
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1,Ret=0;pushdown(x);
    if(ql<=mid) Ret+=query(x<<1,l,mid,ql,qr);
    if(qr>mid)  Ret+=query(x<<1|1,mid+1,r,ql,qr);
    return Ret;
}

void dfs1(int x,int anc)
{
    fa[x]=anc;siz[x]=1;dep[x]=dep[anc]+1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==anc) continue;
        dfs1(v,x);siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}

void dfs2(int x,int tp)
{
    pos[x]=++dft;top[x]=tp;
    if(son[x]) dfs2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==son[x]||v==fa[x]) continue;
        dfs2(v,v);
    }
}

void Cover(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        change(1,1,n,pos[top[x]],pos[x]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    if(x!=y)  change(1,1,n,pos[x]+1,pos[y]);
}

int Query(int x,int y)
{
    int Ret=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        Ret+=query(1,1,n,pos[top[x]],pos[x]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    if(x!=y) Ret+=query(1,1,n,pos[x]+1,pos[y]);
    return Ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) Fa[i]=i;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        if(u>v) swap(u,v);
        g[u].insert(v);
    }
    for(int c,a,b;;)
    {
        scanf("%d",&c);
        if(c==-1) break;
        scanf("%d%d",&a,&b);
        Tp[++cnt]=c;
        if(c==1) Q[cnt]=make_pair(a,b);
        else
        {
            if(a>b) swap(a,b);
            g[a].erase(b);
            Q[cnt]=make_pair(a,b);
        }
    }
    for(int i=1;i<=n;i++)
        for(set<int>::iterator it=g[i].begin();it!=g[i].end();++it)
        {
            if(find(i)!=find(*it))
            {
                add(i,*it);add(*it,i);
                Fa[find(i)]=find(*it);
            }
            else ng[i].push_back(*it);
        }
    dfs1(1,0);dfs2(1,1);
    build(1,1,n);
    for(int i=1;i<=n;i++)
        for(vector<int>::iterator it=ng[i].begin();it!=ng[i].end();++it)
            Cover(i,*it);
    for(int i=cnt;i;i--)
    {
        if(Tp[i]==1) stk.push(Query(Q[i].fi,Q[i].se));
        else Cover(Q[i].fi,Q[i].se);
    }
    while(stk.size()) printf("%d\n",stk.top()),stk.pop();
}