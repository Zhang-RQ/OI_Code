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
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=100010;
const int MAXM=2E5+5;
namespace President_tree{
    struct node{
        int val,ls,rs;
    }t[MAXN<<4];
    int cnt,rt[MAXN];
    void insert(int &x,int l,int r,int pos,int x_)
    {
        if(cnt>(MAXN<<4)) puts("GG"),exit(0);;
        x=++cnt;
        t[x]=t[x_];
        t[x].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].ls,l,mid,pos,t[x_].ls);
        else insert(t[x].rs,mid+1,r,pos,t[x_].rs);
    }
    int query(int x,int l,int r,int ql,int qr)
    {
        if(!x) return 0;
        if(ql<=l&&r<=qr) return t[x].val;
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr);
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr);
        return ret;
    }
}
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,n,m,t,vall[MAXN],bl[MAXN],x,y,k,cnt;
int fa[MAXN][21],val[MAXN],siz[MAXN],dep[MAXN],lstans;
char opt[MAXN];
inline void add(int u,int v)
{
    if(cnt_e>MAXM) puts("GG"),exit(0);
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
int get_lca(int x,int y)
{
    // for(int i=0;i<=20;i++) printf("%d ",fa[x][i]);
    // puts("");
    // for(int j=0;j<=20;j++) printf("%d ",fa[y][j]);
    // puts("");
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    if(dep[x]!=dep[y])
        for(int i=20;i>=0;i--)
            if(dep[fa[x][i]]>=dep[y])
                x=fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    if(x!=y) return fa[x][0];
    return x;
}
void dfs(int x,int father,int rtt)
{
    // printf("%d->%d\n",father,x);
    using President_tree::rt;using President_tree::insert;
    fa[x][0]=father;dep[x]=dep[father]+1;
    bl[x]=rtt;siz[bl[x]]++;
    for(int i=1;i<=20;i++)  fa[x][i]=fa[fa[x][i-1]][i-1];
    insert(rt[x],1,cnt,val[x],rt[father]);
    // printf("%d %d %d\n",x,father,val[x]);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(father==v) continue;
        dfs(v,x,rtt);
    }
}
int query(int l,int r,int u,int v,int lc,int k)
{
    if(l==r) return l;
    using President_tree::query;
    using President_tree::rt;
    int mid=(l+r)>>1;
    int lsiz=query(rt[u],1,cnt,l,mid)+query(rt[v],1,cnt,l,mid)-2*query(rt[fa[lc][0]],1,cnt,l,mid)-(val[lc]<=mid&&val[lc]>=l);
    // printf("(%d-(%d)->%d)%d--%d--%d %d=%d+%d-2*%d-%d\n",u,lc,v,l,mid,r,lsiz,query(rt[u],1,cnt,l,mid),query(rt[v],1,cnt,l,mid),query(rt[fa[lc][0]],1,cnt,l,mid),(val[lc]<=mid&&val[lc]>=l));
    if(lsiz>=k) return ::query(l,mid,u,v,lc,k);
    else return ::query(mid+1,r,u,v,lc,k-lsiz);
}
void link(int x,int y)
{
    add(x,y);add(y,x);
    if(siz[bl[x]]>siz[bl[y]]) swap(x,y);
    dfs(x,y,bl[y]);
}
int main()
{
    scanf("%*d");
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]),vall[i]=val[i];
    for(int i=1;i<=m;i++)
    {
        static int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    sort(vall+1,vall+1+n);
    cnt=unique(vall+1,vall+1+n)-vall-1;
    for(int i=1;i<=n;i++) val[i]=lower_bound(vall+1,vall+1+cnt,val[i])-vall;
    for(int i=1;i<=n;i++) printf("%d ",val[i]);
    puts("");
    for(int i=1;i<=n;i++)
        if(!bl[i]) dfs(i,0,i);
    for(int i=1;i<=t;i++)
    {
        scanf("%s",opt+1);
        switch(opt[1])
        {
            case 'Q': scanf("%d%d%d",&x,&y,&k);x^=lstans,y^=lstans,k^=lstans;printf("%d\n",lstans=vall[query(1,cnt,x,y,get_lca(x,y),k)]);break;
            case 'L': scanf("%d%d",&x,&y);x^=lstans,y^=lstans;link(x,y);break;
        }
    }
}
