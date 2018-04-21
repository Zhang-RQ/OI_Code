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
const int MAXN=200010;
const int MAXM=200010;
const int INF=1<<30;
struct E{int u,v;} Edge[MAXM];
int ke[MAXN],m,n,k,tp,rt[MAXM],lstans,l,r;
namespace LCT{
    #define ls(x) t[x].son[0]
    #define rs(x) t[x].son[1]
    #define fa(x) t[x].fa
    struct node{
        int son[2],fa,mn,val;
        bool rev;
    }t[MAXN+MAXM];
    inline bool rson(int x)  {return rs(fa(x))==x;}
    inline bool isroot(int x) {return ls(fa(x))!=x&&rs(fa(x))!=x;}
    inline void pushup(int x)  {t[x].mn=min(t[x].val,min(t[ls(x)].mn,t[rs(x)].mn));}
    inline void pushdown(int x) {if(t[x].rev) t[ls(x)].rev^=1,t[rs(x)].rev^=1,swap(ls(x),rs(x)),t[x].rev=0;}
    void pd(int x) {if(!isroot(x)) pd(fa(x));pushdown(x);}
    void rotate(int x)
    {
        int y=fa(x),z=fa(y);
        bool rsx=rson(x),rsy=rson(y);
        if(!isroot(y)) t[z].son[rsy]=x;
        t[y].son[rsx]=t[x].son[!rsx];
        t[x].son[!rsx]=y;
        t[x].fa=z;t[y].fa=x;
        t[t[y].son[rsx]].fa=y;
        pushup(y);pushup(x);
    }
    inline void splay(int x)
    {
        pd(x);
        while(!isroot(x))
        {
            if(!isroot(fa(x))) rotate(rson(x)==rson(fa(x))?fa(x):x);
            rotate(x);
        }
    }
    inline void access(int x)
    {
        for(int y=0;x;y=x,x=t[x].fa)
            splay(x),t[x].son[1]=y,pushup(x);
    }
    inline void makeroot(int x)
    {
        access(x);splay(x);
        t[x].rev^=1;
    }
    inline int findroot(int x)
    {
        access(x);splay(x);
        while(ls(x)) x=ls(x);
        return x;
    }
    inline void split(int x,int y)
    {
        makeroot(x);
        access(y);
        splay(y);
    }
    inline void link(int x,int y)
    {
        makeroot(x);
        if(findroot(y)==x) return;
        t[x].fa=y;
    }
    inline void cut(int x,int y)
    {
        split(x,y);
        if(ls(y)==x) ls(y)=fa(x)=0;
    }
    int query(int x,int y)
    {
        if(x==y) return 0;
        makeroot(x);
        if(findroot(y)!=x) return 0;
        access(y);splay(y);
        return t[y].mn;
    }
    #undef ls
    #undef rs
    #undef fa
}
namespace President_tree{
    struct node{
        int ls,rs,val;
    }t[MAXN<<5];
    int cnt;
    void insert(int &x,int l,int r,int pos,int _x)
    {
        x=++cnt;
        t[x]=t[_x];
        t[x].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) insert(t[x].ls,l,mid,pos,t[_x].ls);
        else insert(t[x].rs,mid+1,r,pos,t[_x].rs);
    }
    int query(int x,int l,int r,int ql,int qr,int _x)
    {
        if(ql<=l&&r<=qr) return t[x].val-t[_x].val;
        int ret=0,mid=(l+r)>>1;
        if(ql<=mid) ret+=query(t[x].ls,l,mid,ql,qr,t[_x].ls);
        if(qr>mid)  ret+=query(t[x].rs,mid+1,r,ql,qr,t[_x].rs);
        return ret;
    }
}
int main()
{
    LCT::t[0].val=LCT::t[0].mn=INF;
    scanf("%d%d%d%d",&n,&m,&k,&tp);
    for(int i=1;i<=m;i++) scanf("%d%d",&Edge[i].u,&Edge[i].v);
    for(int i=1;i<=n+m;i++) LCT::t[i].val=LCT::t[i].mn=INF;
    for(int i=1;i<=m;i++)
    {
        if(Edge[i].u==Edge[i].v) {ke[i]=i;continue;}
        LCT::t[n+i].val=i;
        ke[i]=LCT::query(Edge[i].u,Edge[i].v);
        if(ke[i]!=0) LCT::cut(Edge[ke[i]].u,ke[i]+n),LCT::cut(Edge[ke[i]].v,ke[i]+n);
        LCT::link(Edge[i].u,i+n);LCT::link(Edge[i].v,i+n);
    }
    for(int i=1;i<=m;i++) President_tree::insert(rt[i],0,m,ke[i],rt[i-1]);
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&l,&r);
        if(tp) l^=lstans,r^=lstans;
        lstans=n-President_tree::query(rt[r],0,m,0,l-1,rt[l-1]);
        printf("%d\n",lstans);
    }
}
