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
inline bool in(const int& x1,const int& y1,const int& x2,const int& y2,const int& X1,const int& Y1,const int& X2,const int& Y2)  {return X1<=x1&&x2<=X2&&Y1<=y1&&y2<=Y2;}
inline bool out(const int& x1,const int& y1,const int& x2,const int& y2,const int& X1,const int& Y1,const int& X2,const int& Y2) {return x1>X2||x2<X1||y1>Y2||y2<Y1;}
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
int D,cnt,n,m,rt;
struct node{
    int son[2],val,co[2],x[2],y[2];
    ll sum;
}t[MAXN];
struct Point{
    int co[2],val;
    inline bool operator < (const Point &rhs) const
    {
        return co[D]<rhs.co[D];
    }
}pnt[MAXN];
void pushup(int x)
{
    t[x].sum=t[x].val;
    if(ls(x))
       t[x].sum+=t[ls(x)].sum,
       t[x].x[0]=min(t[x].x[0],t[ls(x)].x[0]),t[x].y[0]=min(t[x].y[0],t[ls(x)].y[0]),
       t[x].x[1]=max(t[x].x[1],t[ls(x)].x[1]),t[x].y[1]=max(t[x].y[1],t[ls(x)].y[1]);
   if(rs(x))
       t[x].sum+=t[rs(x)].sum,
       t[x].x[0]=min(t[x].x[0],t[rs(x)].x[0]),t[x].y[0]=min(t[x].y[0],t[rs(x)].y[0]),
       t[x].x[1]=max(t[x].x[1],t[rs(x)].x[1]),t[x].y[1]=max(t[x].y[1],t[rs(x)].y[1]);
}
void build(int &x,int l,int r,int d)
{
    int mid=(l+r)>>1;
    D=d;x=++cnt;
    nth_element(pnt+l,pnt+mid,pnt+r+1);
    t[x].x[0]=t[x].x[1]=t[x].co[0]=pnt[mid].co[0];
    t[x].y[0]=t[x].y[1]=t[x].co[1]=pnt[mid].co[1];
    t[x].sum=t[x].val=pnt[mid].val;
    if(l<mid) build(ls(x),l,mid-1,d^1);
    if(r>mid) build(rs(x),mid+1,r,d^1);
    pushup(x);
}
ll query(int x,const int& x1,const int& y1,const int& x2,const int& y2)
{
    if(in(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1],x1,y1,x2,y2)) return t[x].sum;
    if(out(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1],x1,y1,x2,y2)) return 0;
    ll ret=0;
    if(in(t[x].co[0],t[x].co[1],t[x].co[0],t[x].co[1],x1,y1,x2,y2)) ret+=t[x].val;
    if(ls(x)) ret+=query(ls(x),x1,y1,x2,y2);
    if(rs(x)) ret+=query(rs(x),x1,y1,x2,y2);
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&pnt[i].co[0],&pnt[i].co[1],&pnt[i].val);
    build(rt,1,n,0);
    int x1,y1,x2,y2;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        printf("%lld\n",query(rt,x1,y1,x2,y2));
    }
}
