#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN=200100;
#define ls t[x].son[0]
#define rs t[x].son[1]
int D,cnt,rt,x1,x2,y1,y2,lstans,tot;
struct Point{
    int co[2],val;
    bool operator < (const Point &rhs) const
    {
        return co[D]<rhs.co[D];
    }
    Point(){}
    Point(int x,int y,int val):co{x,y},val(val){}
}pnt[MAXN];
struct node{
    int co[2],x[2],y[2],son[2],sum,val;
    inline void clear()
    {
        co[0]=co[1]=x[0]=x[1]=y[0]=y[1]=son[0]=son[1]=sum=val=0;
    }
}t[MAXN];
void pushup(int x)
{
    t[x].sum=t[x].val;
    if(ls)
        t[x].x[0]=min(t[x].x[0],t[ls].x[0]),t[x].x[1]=max(t[x].x[1],t[ls].x[1]),
        t[x].y[0]=min(t[x].y[0],t[ls].y[0]),t[x].y[1]=max(t[x].y[1],t[ls].y[1]),
        t[x].sum+=t[ls].sum;
    if(rs)
        t[x].x[0]=min(t[x].x[0],t[rs].x[0]),t[x].x[1]=max(t[x].x[1],t[rs].x[1]),
        t[x].y[0]=min(t[x].y[0],t[rs].y[0]),t[x].y[1]=max(t[x].y[1],t[rs].y[1]),
        t[x].sum+=t[rs].sum;
}
void insert(int &x,int X,int Y,int val,int d)
{
    if(!x)
    {
        x=++cnt;
        t[x].co[0]=X;t[x].co[1]=Y;t[x].sum=val;t[x].val=val;
        t[x].x[0]=t[x].x[1]=X;t[x].y[0]=t[x].y[1]=Y;
        return;
    }
    if(t[x].co[0]==X&&t[x].co[1]==Y) {t[x].val+=val;t[x].sum+=val;return;}
    if(!d)  insert(t[x].son[t[x].co[d]<X],X,Y,val,d^1);
    else    insert(t[x].son[t[x].co[d]<Y],X,Y,val,d^1);
    pushup(x);
}
void build(int &x,int l,int r,int d)
{
    //puts("233");
    x=++cnt;D=d;
    int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+1+r);
    t[x].clear();
    t[x].co[0]=t[x].x[0]=t[x].x[1]=pnt[mid].co[0];
    t[x].co[1]=t[x].y[0]=t[x].y[1]=pnt[mid].co[1];
    t[x].val=t[x].sum=pnt[mid].val;
    if(l<mid) build(ls,l,mid-1,d^1);
    if(r>mid) build(rs,mid+1,r,d^1);
    pushup(x);
}
bool in(int X1,int Y1,int X2,int Y2)  {return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2;}
bool out(int X1,int Y1,int X2,int Y2) {return x1>X2||x2<X1||Y1>y2||Y2<y1;}
void query(int x)
{
    if(!x) return;
    // printf("x=%d\n",x);
    if(in(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1])) {lstans+=t[x].sum;return;}
    if(out(t[x].x[0],t[x].y[0],t[x].x[1],t[x].y[1])) {return;}
    if(in(t[x].co[0],t[x].co[1],t[x].co[0],t[x].co[1])) lstans+=t[x].val;
    query(ls);query(rs);
}
int n,X1,Y1,X2,Y2,val,opt;
int main()
{
    scanf("%d",&n);
    for(int i=1;i;i++)
    {
        scanf("%d",&opt);
        if(opt==3) break;
        if(opt==1)
        {
            scanf("%d%d%d",&X1,&Y1,&val);
            X1^=lstans;Y1^=lstans;val^=lstans;
            insert(rt,X1,Y1,val,0);
            pnt[++tot]=Point(X1,Y1,val);
        }
        else
        {
            scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2);
            x1=X1^lstans;y1=Y1^lstans;x2=X2^lstans;y2=Y2^lstans;
            lstans=0;query(rt);
            printf("%d\n",lstans);
        }
        if(i%10000==0) {cnt=0;build(rt,1,tot,0);}
    }
}
