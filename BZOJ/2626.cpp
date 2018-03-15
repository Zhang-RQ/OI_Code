<<<<<<< HEAD
//WA
=======
>>>>>>> 025c84597fb0e7c3162be5cc7125992f91354572
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
const int MAXN=100100;
int D,cnt;
inline ll sqr(const ll &x) {return x*x;}
struct Point{
    int co[2];
    inline bool operator < (const Point &rhs) const
    {
        if(co[D]!=rhs.co[D]) return co[D]<rhs.co[D];
        return co[D^1]<rhs.co[D^1];
    }
}pnt[MAXN];
struct node{
    int son[2],mn[2],mx[2],co[2],num;
}t[MAXN];
struct data{
    ll dis;int num;
    inline bool operator < (const data &rhs) const
    {
        return dis>rhs.dis||(dis==rhs.dis&&num<rhs.num);
    }
};
priority_queue<data> pq;
inline void pushup(int x)
{
    if(ls)
        t[x].mn[0]=min(t[x].mn[0],t[ls].mn[0]),t[x].mn[1]=min(t[x].mn[1],t[ls].mn[1]),
        t[x].mx[0]=max(t[x].mx[0],t[ls].mx[1]),t[x].mx[1]=max(t[x].mx[1],t[ls].mx[1]);
    if(rs)
        t[x].mn[0]=min(t[x].mn[0],t[rs].mn[0]),t[x].mn[1]=min(t[x].mn[1],t[rs].mn[1]),
        t[x].mx[0]=max(t[x].mx[0],t[rs].mx[1]),t[x].mx[1]=max(t[x].mx[1],t[rs].mx[1]);
}
void build(int &x,int l,int r,int d)
{
    x=++cnt;D=d;
    int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+r+1);
    t[x].co[0]=t[x].mn[0]=t[x].mx[0]=pnt[mid].co[0];
    t[x].co[1]=t[x].mn[1]=t[x].mx[1]=pnt[mid].co[1];
    t[x].num=mid;
    if(l<mid) build(ls,l,mid-1,d^1);
    if(r>mid) build(rs,mid+1,r,d^1);
    pushup(x);
}
inline ll calc(const int &x,const int &X,const int &Y) {return max(sqr(X-t[x].mn[0]),sqr(X-t[x].mx[0]))+max(sqr(Y-t[x].mn[1]),sqr(Y-t[x].mx[1]));}
inline ll dis(int x,int X,int Y) {return sqr(t[x].co[0]-X)+sqr(t[x].co[1]-Y);}
void query(int x,int X,int Y)
{
    if(!x) return;
    // printf("num=%d\n",t[x].num);
    ll dl=-4,dr=-4;
    if(ls) dl=calc(ls,X,Y);
    if(rs) dr=calc(rs,X,Y);
    // printf("ls=%d,dl=%lld\n",t[ls].num,dl);
    // printf("rs=%d,dr=%lld\n",t[rs].num,dr);
    if(dis(x,X,Y)>pq.top().dis||(dis(x,X,Y)==pq.top().dis&&t[x].num<pq.top().num))
        pq.pop(),pq.push((data){dis(x,X,Y),t[x].num});
    if(dl>dr)
    {
        if(dl>=pq.top().dis) query(ls,X,Y);
        if(dr>=pq.top().dis) query(rs,X,Y);
    }
    else
    {
        if(dr>=pq.top().dis) query(rs,X,Y);
        if(dl>=pq.top().dis) query(ls,X,Y);
    }
}
int n,m,xx,yy,kk,rt;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&pnt[i].co[0],&pnt[i].co[1]);
    build(rt,1,n,0);
    // for(int i=1;i<=n;i++)
    //     printf("%d %d (%d,%d) (%d,%d)--(%d,%d)\n",i,t[i].num,t[i].co[0],t[i].co[1],t[i].mn[0],t[i].mn[1],t[i].mx[0],t[i].mx[1]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&xx,&yy,&kk);
        while(pq.size()) pq.pop();
        for(int j=1;j<=kk;j++)
            pq.push((data){-1,0});
        query(rt,xx,yy);
        printf("%d\n",pq.top().num);
    }
}
