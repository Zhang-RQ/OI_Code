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
const int INF=(1<<30);
const int MAXN=1E5+10;
const int MAXM=2E5+5;
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
struct Matrix{
    int a,b,c,d;
    Matrix(){a=b=c=d=0;}
    Matrix(int _,int __,int ___,int ____):a(_),b(__),c(___),d(____){}
    inline Matrix operator * (const Matrix &rhs) const
    {
        Matrix ret;
        ret.a=max(a+rhs.a,b+rhs.c);ret.b=max(a+rhs.b,b+rhs.d);
        ret.c=max(c+rhs.a,d+rhs.c);ret.d=max(c+rhs.b,d+rhs.d);
        return ret;
    }
}t[MAXN<<3];
int g[MAXN][2],fa[MAXN],dep[MAXN],top[MAXN],bot[MAXN],siz[MAXN],son[MAXN];
int pos[MAXN],cnt,tp[MAXN],n,val[MAXN],vv[MAXN],m;
inline void pushup(const int &x) {t[x]=t[x<<1|1]*t[x<<1];}
inline void build(int x,int l,int r,int bl,int br)
{
    if(l==r)
    {
        t[x].a=g[l][1];t[x].b=g[l][0]+vv[l];t[x].c=g[l][1];t[x].d=-INF;
        return;
    }
    int mid=(l+r)>>1;
    if(bl<=mid) build(x<<1,l,mid,bl,br);
    if(br>mid) build(x<<1|1,mid+1,r,bl,br);
    pushup(x);
}
void change(int x,int l,int r,int pos,const Matrix &rhs)
{
    if(l==r) {t[x]=rhs;return;}
    int mid=(l+r)>>1;
    if(pos<=mid) change(x<<1,l,mid,pos,rhs);
    else change(x<<1|1,mid+1,r,pos,rhs);
    pushup(x);
}
Matrix query(int x,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr) return t[x];
    int mid=(l+r)>>1;
    if(qr<=mid) return query(x<<1,l,mid,ql,qr);
    if(ql>mid)  return query(x<<1|1,mid+1,r,ql,qr);
    else return query(x<<1|1,mid+1,r,ql,qr)*query(x<<1,l,mid,ql,qr);
}
void dfs1(int x,int father)
{
    fa[x]=father;dep[x]=dep[fa[x]]+1;
    siz[x]=1;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]) continue;
        dfs1(v,x);
        siz[x]+=siz[v];
        if(siz[son[x]]<siz[v]) son[x]=v;
    }
}
void dfs2(int x,int tp)
{
    top[x]=tp;bot[tp]=x;
    pos[x]=++cnt;vv[pos[x]]=val[x];
    if(son[x]) dfs2(son[x],tp);
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
void change(int x,int y)
{
    val[x]=y;vv[pos[x]]=y;
    while(x)
    {
        Matrix _t=query(1,1,n,pos[top[x]],pos[bot[top[x]]]),_pos=query(1,1,n,pos[x],pos[x]);
        int _f0=max(_t.a,_t.c),_f1=max(_t.b,max(_t.d,0)),_g0=_f0,_g1=max(_f0,_f1);
        if(y) _pos.b=g[pos[x]][0]+y,y=0;
        else _pos.a=g[pos[x]][1],_pos.b=g[pos[x]][0]+val[x],_pos.c=g[pos[x]][1],_pos.d=-INF;
        change(1,1,n,pos[x],_pos);
        _t=query(1,1,n,pos[top[x]],pos[bot[top[x]]]);
        int f0=max(_t.a,_t.c),f1=max(_t.b,max(_t.d,0)),g0=f0,g1=max(f0,f1);
        if(g0==_g0&&g1==_g1) break;
        g[pos[fa[top[x]]]][0]=g[pos[fa[top[x]]]][0]-_g0+g0;
        g[pos[fa[top[x]]]][1]=g[pos[fa[top[x]]]][1]-_g1+g1;
        x=fa[top[x]];
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&val[i]);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    cnt=0;
    for(int i=1;i<=n;i++)
        if(top[i]==i) tp[++cnt]=i;
    sort(tp+1,tp+1+cnt,[](int a,int b)->bool{return dep[a]>dep[b];});
    for(int i=1;i<=cnt;i++)
    {
        int x=tp[i],bt=bot[x];
        build(1,1,n,pos[x],pos[bt]);
        Matrix _t=query(1,1,n,pos[x],pos[bt]);
        int f0=max(_t.a,_t.c),f1=max(_t.b,max(_t.d,0));
        g[pos[fa[x]]][0]+=f0;g[pos[fa[x]]][1]+=max(f0,f1);
    }
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);change(x,y);
        Matrix _t=query(1,1,n,pos[1],pos[bot[1]]);
        printf("%d\n",max(max(_t.a,_t.c),max(_t.b,max(_t.d,0))));
    }
    #ifdef LOCAL
        system("pause");
    #endif
}