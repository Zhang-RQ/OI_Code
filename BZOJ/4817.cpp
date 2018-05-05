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
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct __edge{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,fa[MAXN],jmp[MAXN][21],son[MAXN],siz[MAXN],top[MAXN],cnt,dfn[MAXN],dep[MAXN];
int col_top[MAXN<<1],col_bot[MAXN<<1],n,m,u,v,col_cnt,opt,x,y,nfd[MAXN];
namespace Segment_tree{
    struct node{
        int val,col,tag;
    }t[MAXN<<4];
    inline void pushup(const int &x) {t[x].val=max(t[x<<1].val,t[x<<1|1].val);}
    inline void pushdown(const int &x)
    {
        if(t[x].tag)
        {
            t[x<<1].val+=t[x].tag;
            t[x<<1|1].val+=t[x].tag;
            t[x<<1].tag+=t[x].tag;
            t[x<<1|1].tag+=t[x].tag;
            t[x].tag=0;
        }
    }
    void build(int x,int l,int r)
    {
        if(l==r) {t[x].val=dep[nfd[l]];t[x].col=nfd[l];return;}
        int mid=(l+r)>>1;
        build(x<<1,l,mid);build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void changeV(int x,int l,int r,int cl,int cr,int val)
    {
        if(cl<=l&&r<=cr) {t[x].val+=val;t[x].tag+=val;return;}
        int mid=(l+r)>>1;pushdown(x);
        if(cl<=mid) changeV(x<<1,l,mid,cl,cr,val);
        if(cr>mid)  changeV(x<<1|1,mid+1,r,cl,cr,val);
        pushup(x);
    }
    void changeC(int x,int l,int r,int cl,int cr,int col) // 标记永久化
    {
        if(cl<=l&&r<=cr) {t[x].col=col;return;}
        int mid=(l+r)>>1;pushdown(x);
        if(cl<=mid) changeC(x<<1,l,mid,cl,cr,col);
        if(cr>mid)  changeC(x<<1|1,mid+1,r,cl,cr,col);
    }
    int queryV(int x,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr) return t[x].val;
        int mid=(l+r)>>1,ret=0;pushdown(x);
        if(ql<=mid) ret=max(ret,queryV(x<<1,l,mid,ql,qr));
        if(qr>mid)  ret=max(ret,queryV(x<<1|1,mid+1,r,ql,qr));
        return ret;
    }
    int queryC(int x,int l,int r,int pos)
    {
        if(l==r) return t[x].col;
        int mid=(l+r)>>1,ret=t[x].col;
        if(pos<=mid) ret=max(ret,queryC(x<<1,l,mid,pos));
        if(pos>mid)  ret=max(ret,queryC(x<<1|1,mid+1,r,pos));
        return ret;
    }
}
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
void dfs_1(int x,int father)
{
    siz[x]=1;dep[x]=dep[father]+1;
    jmp[x][0]=fa[x]=father;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==father) continue;
        dfs_1(v,x);
        siz[x]+=siz[v];
        if(siz[v]>siz[son[x]]) son[x]=v;
    }
}
void dfs_2(int x,int tp)
{
    dfn[x]=++cnt;top[x]=tp;
    nfd[cnt]=x;
    if(son[x])  dfs_2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
        if(Edge[i].v!=fa[x]&&Edge[i].v!=son[x])
            dfs_2(Edge[i].v,Edge[i].v);
}
void init()
{
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            jmp[i][j]=jmp[jmp[i][j-1]][j-1];
}
int LCA(int x,int y,bool tp) //tp==0 LCA,tp==1 dep[x]>dep[y],fa[ret]==y
{
    if(tp)
    {
        for(int i=20;i>=0;i--)
            if(dep[jmp[x][i]]>dep[y])
                x=jmp[x][i];
        return x;
    }
    else
    {
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=20;i>=0;i--)
            if(dep[jmp[x][i]]>=dep[y])
                x=jmp[x][i];
        if(x==y) return x;
        for(int i=20;i>=0;i--)
            if(jmp[x][i]!=jmp[y][i])
                x=jmp[x][i],y=jmp[y][i];
        return fa[x];
    }
}
void paint_col(int x,int col)
{
    col_top[col]=1;col_bot[col]=x;
    int c,r,v,nl=0,nr=0,lstc=0;
    while(x)
    {
        c=Segment_tree::queryC(1,1,n,dfn[x]);
        v=Segment_tree::queryV(1,1,n,dfn[x],dfn[x]);
        r=col_top[c];
        if(dep[r]<dep[top[x]])
        {
            Segment_tree::changeV(1,1,n,dfn[top[x]],dfn[top[x]]+siz[top[x]]-1,1-v);
            Segment_tree::changeC(1,1,n,dfn[top[x]],dfn[x],col);
            if(nl) Segment_tree::changeV(1,1,n,nl,nr,v-1);
        }
        else
        {
            Segment_tree::changeV(1,1,n,dfn[r],dfn[r]+siz[r]-1,1-v);
            Segment_tree::changeC(1,1,n,dfn[r],dfn[x],col);
            if(nl) Segment_tree::changeV(1,1,n,nl,nr,v-1);
        }
        if(col_bot[c]!=x)
        {
            int lca=LCA(col_bot[c],x,1);
            if(nl!=dfn[lca])
            {
                Segment_tree::changeV(1,1,n,dfn[lca],dfn[lca]+siz[lca]-1,1);
                lstc=lca;
            }
        }
        if(dep[r]<dep[top[x]])
            nl=dfn[top[x]],nr=dfn[top[x]]+siz[top[x]]-1,x=fa[top[x]];
        else nl=dfn[r],nr=dfn[r]+siz[r]-1,x=fa[r],col_top[c]=lstc;
    }
}
int askV(int x,int y)
{
    int lca=LCA(x,y,0);
    return Segment_tree::queryV(1,1,n,dfn[x],dfn[x])+Segment_tree::queryV(1,1,n,dfn[y],dfn[y])-2*Segment_tree::queryV(1,1,n,dfn[lca],dfn[lca])+1;
}
int ask_maxV(int x)
{
    return Segment_tree::queryV(1,1,n,dfn[x],dfn[x]+siz[x]-1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    for(int i=1;i<=n;i++) col_top[i]=col_bot[i]=i;
    col_cnt=n;
    dfs_1(1,0);dfs_2(1,1);
    init();Segment_tree::build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:scanf("%d",&x);paint_col(x,++col_cnt);break;
            case 2:scanf("%d%d",&x,&y);printf("%d\n",askV(x,y));break;
            case 3:scanf("%d",&x);printf("%d\n",ask_maxV(x));break;
        }
    }
}
