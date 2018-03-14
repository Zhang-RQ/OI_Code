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
const int P=1E9+7;
#define ls t[x].son[0]
#define rs t[x].son[1]
const int MAXN=1E5+5;
const int MAXM=2E5+5;
struct node{
    int nxt,v;
}Edge[MAXM];
int head[MAXN],cnt_e,D,cnt;
inline void add(int u,int v)
{
    Edge[++cnt_e].v=v;
    Edge[cnt_e].nxt=head[u];
    head[u]=cnt_e;
}
struct Point{
    int co[2];
    Point(){}
    Point(int x,int y):co{x,y}{}
    inline bool operator < (const Point &rhs) const
    {
        if(co[D]!=rhs.co[D]) return co[D]<rhs.co[D];
        else return co[D^1]<rhs.co[D^1];
    }
}pnt[MAXN];
struct NODE{
    int co[2],son[2],col,tag,x[2],y[2];
    inline void clear(){co[0]=co[1]=son[0]=son[1]=col=tag=x[0]=x[1]=y[0]=y[1]=0;}
}t[MAXN];
int dep[MAXN],siz[MAXN],dfn[MAXN];
int dfst=0,n;
void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;
    siz[x]=1;dfn[x]=++dfst;
    for(int i=head[x];i;i=Edge[i].nxt)
    {
        int v=Edge[i].v;
        if(v==fa) continue;
        dfs(v,x);
        siz[x]+=siz[v];
    }
}
inline void pushup(int x)
{
    if(ls)
        t[x].x[0]=min(t[x].x[0],t[ls].x[0]),t[x].y[0]=min(t[x].y[0],t[ls].y[0]),
        t[x].x[1]=max(t[x].x[1],t[ls].x[1]),t[x].y[1]=max(t[x].y[1],t[ls].y[1]);
    if(rs)
        t[x].x[0]=min(t[x].x[0],t[rs].x[0]),t[x].y[0]=min(t[x].y[0],t[rs].y[0]),
        t[x].x[1]=max(t[x].x[1],t[rs].x[1]),t[x].y[1]=max(t[x].y[1],t[rs].y[1]);
}
inline void pushdown(int x)
{
    if(t[x].tag)
    {
        t[ls].col=t[rs].col=t[x].tag;
        t[ls].tag=t[rs].tag=t[x].tag;
        t[x].tag=0;
    }
}
void build(int &x,int l,int r,int d)
{
    if(l>r) return;
    D=d;x=++cnt;
    int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+1+r);
    t[x].clear();
    t[x].x[0]=t[x].x[1]=t[x].co[0]=pnt[mid].co[0];
    t[x].y[0]=t[x].y[1]=t[x].co[1]=pnt[mid].co[1];
    t[x].col=1;
    if(l<mid) build(ls,l,mid-1,d^1);
    if(r>mid) build(rs,mid+1,r,d^1);
    pushup(x);
}
inline bool in(const int &X1,const int &Y1,const int &X2,const int &Y2,const int &x1,const int &y1,const int &x2,const int &y2)  {return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2;}
inline bool out(const int &X1,const int &Y1,const int &X2,const int &Y2,const int &x1,const int &y1,const int &x2,const int &y2) {return x1>X2||x2<X1||Y1>y2||Y2<y1;}
void change(int x,int X1,int Y1,int X2,int Y2,int col)
{
    pushdown(x);
    //printf("(c)x=%d (%d,%d)--(%d,%d) %d %d \n",x,X1,Y1,X2,Y2,t[x].co[0],t[x].co[1]);
    if(in(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1],X1,Y1,X2,Y2)) {t[x].col=col;t[x].tag=col;return;}
    if(X1<=t[x].co[0]&&t[x].co[0]<=X2&&Y1<=t[x].co[1]&&t[x].co[1]<=Y2) /*printf("edit:%d\n",x),*/t[x].col=col;
    if(out(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1],X1,Y1,X2,Y2)) return;
    if(ls) change(ls,X1,Y1,X2,Y2,col);
    if(rs) change(rs,X1,Y1,X2,Y2,col);
}
int query(int x,int X,int Y,int d)
{
    pushdown(x);
    //printf("(q)x=%d %d %d %d %d %d\n",x,X,Y,t[x].co[0],t[x].co[1],d);
    if(X==t[x].co[0]&&Y==t[x].co[1]) return t[x].col;
    int lrson=0;
    if(d) lrson=t[x].co[d]<Y||(t[x].co[d]==Y&&t[x].co[d^1]<X);
    else lrson=t[x].co[d]<X||(t[x].co[d]==X&&t[x].co[d^1]<Y);
    return query(t[x].son[lrson],X,Y,d^1);
}
int T,c,q,u,v,a,l,rt;
ll ans=0;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        dfst=0;cnt_e=0;memset(head,0,sizeof head);ans=0;
        scanf("%d%d%d",&n,&c,&q);
        for(int i=2;i<=n;i++)
            scanf("%d",&v),add(i,v),add(v,i);
        dfs(1,0);
        for(int i=1;i<=n;i++)
            pnt[i]=Point(dfn[i],dep[i]);
        rt=cnt=0;build(rt,1,n,0);
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d%d",&a,&l,&c);
            if(c==0) (ans+=1ll*i*query(rt,dfn[a],dep[a],0)%P)%=P;
            else change(rt,dfn[a],dep[a],dfn[a]+siz[a]-1,dep[a]+l,c);
        }
        printf("%lld\n",ans);
    }
}
