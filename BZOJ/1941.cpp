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
const int MAXN=500005;
const int INF=1<<30;
#define ls t[x].son[0]
#define rs t[x].son[1]
int D,AnsMx,AnsMn;
inline void cmin(int &a,int &b) {a=a<b?a:b;}
inline void cmax(int &a,int &b) {a=a>b?a:b;}
struct Point{
    int co[2];
    bool operator < (const Point &rhs) const
    {
        return co[D]<rhs.co[D];
    }
}pnt[MAXN];
struct node{
    int co[2],son[2],x[2],y[2];
}t[MAXN];
int n,m,cnt;
void pushup(int x)
{
    if(ls)
        cmin(t[x].x[0],t[ls].x[0]),cmin(t[x].y[0],t[ls].y[0]),
        cmax(t[x].x[1],t[ls].x[1]),cmax(t[x].y[1],t[ls].y[1]);
    if(rs)
        cmin(t[x].x[0],t[rs].x[0]),cmin(t[x].y[0],t[rs].y[0]),
        cmax(t[x].x[1],t[rs].x[1]),cmax(t[x].y[1],t[rs].y[1]);
}
int askmx(int p,int x,int y)
{
    int ret=0;
    ret=max(abs(t[p].x[0]-x),abs(t[p].x[1]-x))+max(abs(t[p].y[0]-y),abs(t[p].y[1]-y));
    return ret;
}
int askmn(int p,int x,int y)
{
    int ret=0;
    ret=max(0,t[p].x[0]-x)+max(0,x-t[p].x[1])+max(0,t[p].y[0]-y)+max(0,y-t[p].y[1]);
    return ret;
}
void build(int &x,int l,int r,int d)
{
    if(l>r) return;
    D=d;x=++cnt;
    int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+1+r);
    t[x].x[0]=t[x].x[1]=t[x].co[0]=pnt[mid].co[0];
    t[x].y[0]=t[x].y[1]=t[x].co[1]=pnt[mid].co[1];
    if(l<mid) build(ls,l,mid-1,d^1);
    if(mid<r) build(rs,mid+1,r,d^1);
    pushup(x);
}
void querymin(int x,int X,int Y)
{
    int dis=abs(t[x].co[0]-X)+abs(t[x].co[1]-Y);
    if(dis!=0) AnsMn=min(dis,AnsMn);
    int Dl=INF,Dr=INF;
    if(ls) Dl=askmn(ls,X,Y);
    if(rs) Dr=askmn(rs,X,Y);
    if(Dl<Dr)
    {
        if(Dl<AnsMn) querymin(ls,X,Y);
        if(Dr<AnsMn) querymin(rs,X,Y);
    }
    else
    {
        if(Dr<AnsMn) querymin(rs,X,Y);
        if(Dl<AnsMn) querymin(ls,X,Y);
    }
}
void querymax(int x,int X,int Y)
{
    int dis=abs(t[x].co[0]-X)+abs(t[x].co[1]-Y);
    if(dis!=0) AnsMx=max(dis,AnsMx);
    int Dl=0,Dr=0;
    if(ls) Dl=askmx(ls,X,Y);
    if(rs) Dr=askmx(rs,X,Y);
    if(Dl<Dr)
    {
        if(Dr>AnsMx) querymax(rs,X,Y);
        if(Dl>AnsMx) querymax(ls,X,Y);
    }
    else
    {
        if(Dl>AnsMx) querymax(ls,X,Y);
        if(Dr>AnsMx) querymax(rs,X,Y);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&pnt[i].co[0],&pnt[i].co[1]);
    int ans=INF,rt=0;
    build(rt,1,n,0);
    for(int i=1;i<=n;i++)
    {
        AnsMx=0;AnsMn=INF;
        querymin(rt,pnt[i].co[0],pnt[i].co[1]);
        querymax(rt,pnt[i].co[0],pnt[i].co[1]);
        //printf("mn=%d mx=%d\n",AnsMn,AnsMx);
        ans=min(ans,AnsMx-AnsMn);
    }
    printf("%d\n",ans);
}
