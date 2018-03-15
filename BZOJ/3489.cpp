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
#define ls t[x].son[0]
#define rs t[x].son[1]
const int MAXN=100010;
int D,cnt,ans;
struct Point{
    int co[3],val;
    Point(){}
    Point(int x,int y,int z,int _val):co{x,y,z},val(_val){}
    inline bool operator < (const Point &rhs) const
    {
        if(co[D]!=rhs.co[D]) return co[D]<rhs.co[D];
        else if(co[(D+1)%3]!=rhs.co[(D+1)%3]) return co[(D+1)%3]<rhs.co[(D+1)%3];
        return co[(D+2)%3]<rhs.co[(D+2)%3];
    }
}pnt[MAXN];
struct node{
    int co[3],mx[3],mn[3],son[2],val,vl;
}t[MAXN];
inline void pushup(int x)
{
    if(ls)
        t[x].mn[0]=min(t[x].mn[0],t[ls].mn[0]),t[x].mn[1]=min(t[x].mn[1],t[ls].mn[1]),t[x].mn[2]=min(t[x].mn[2],t[ls].mn[2]),
        t[x].mx[0]=max(t[x].mx[0],t[ls].mx[0]),t[x].mx[1]=max(t[x].mx[1],t[ls].mx[1]),t[x].mx[2]=max(t[x].mx[2],t[ls].mx[2]),
        t[x].val=max(t[x].val,t[ls].val);
    if(rs)
        t[x].mn[0]=min(t[x].mn[0],t[rs].mn[0]),t[x].mn[1]=min(t[x].mn[1],t[rs].mn[1]),t[x].mn[2]=min(t[x].mn[2],t[rs].mn[2]),
        t[x].mx[0]=max(t[x].mx[0],t[rs].mx[0]),t[x].mx[1]=max(t[x].mx[1],t[rs].mx[1]),t[x].mx[2]=max(t[x].mx[2],t[rs].mx[2]),
        t[x].val=max(t[x].val,t[rs].val);
}
void build(int &x,int l,int r,int d)
{
    if(l>r) return;
    x=++cnt;int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+r+1);
    t[x].mn[0]=t[x].mx[0]=t[x].co[0]=pnt[mid].co[0];
    t[x].mn[1]=t[x].mx[1]=t[x].co[1]=pnt[mid].co[1];
    t[x].mn[2]=t[x].mx[2]=t[x].co[2]=pnt[mid].co[2];
    t[x].vl=t[x].val=pnt[mid].val;
    if(l<mid) build(ls,l,mid-1,(d+1)%3);
    if(r>mid) build(rs,mid+1,r,(d+1)%3);
    pushup(x);
}
inline bool inside(const int &X1,const int &Y1,const int &Z1,const int &X2,const int &Y2,const int &Z2,const int &x1,const int &y1,const int &z1,const int &x2,const int &y2,const int &z2)  {return X1<=x1&&x2<=X2&&Y1<=y1&&y2<=Y2&&Z1<=z1&&z2<=Z2;}
//小写在大写内
inline bool outside(const int &X1,const int &Y1,const int &Z1,const int &X2,const int &Y2,const int &Z2,const int &x1,const int &y1,const int &z1,const int &x2,const int &y2,const int &z2)  {return X2<x1||X1>x2||Y2<y1||Y1>y2||z1>Z2||z2<Z1;}
void query(int x,int X1,int Y1,int Z1,int X2,int Y2,int Z2)
{
    if(!x) return;
    // printf("%d (%d,%d,%d)--(%d,%d,%d)\n",x,X1,Y1,Z1,X2,Y2,Z2);
    if(outside(X1,Y1,Z1,X2,Y2,Z2,t[x].mn[0],t[x].mn[1],t[x].mn[2],t[x].mx[0],t[x].mx[1],t[x].mx[2])) {return;}
    if(inside(X1,Y1,Z1,X2,Y2,Z2,t[x].mn[0],t[x].mn[1],t[x].mn[2],t[x].mx[0],t[x].mx[1],t[x].mx[2])) {ans=max(ans,t[x].val);return;}
    if(X1<=t[x].co[0]&&t[x].co[0]<=X2&&Y1<=t[x].co[1]&&t[x].co[1]<=Y2&&Z1<=t[x].co[2]&&t[x].co[2]<=Z2) ans=max(ans,t[x].vl);
    query(ls,X1,Y1,Z1,X2,Y2,Z2);query(rs,X1,Y1,Z1,X2,Y2,Z2);
}
int n,m,prepos[MAXN],lstpos[MAXN],tp[MAXN],a[MAXN],rt,x,y,l,r;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        prepos[i]=tp[a[i]];
        tp[a[i]]=i;
    }
    for(int i=n;i>=1;i--)
        tp[i]=n+1;
    for(int i=n;i>=1;i--)
    {
        lstpos[i]=tp[a[i]];
        tp[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
         pnt[i]=Point(i,prepos[i],lstpos[i],a[i]);
    build(rt,1,n,0);ans=0;
    // for(int i=1;i<=n;i++)
    //     printf("i=%d (%d,%d,%d)--(%d,%d,%d) ls=%d rs=%d val=%d pos=(%d,%d,%d) vl=%d\n",i,t[i].mn[0],t[i].mn[1],t[i].mn[2],t[i].mx[0],t[i].mx[1],t[i].mx[2],t[i].son[0],t[i].son[1],t[i].val,t[i].co[0],t[i].co[1],t[i].co[2],t[i].vl);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        l=min((x+ans)%n+1,(y+ans)%n+1);
        r=max((x+ans)%n+1,(y+ans)%n+1);
        ans=0;query(rt,l,0,r+1,r,l-1,n+1);
        printf("%d\n",ans);
    }
}
