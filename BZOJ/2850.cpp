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
const int MAXN=5E4+10;
int D,cnt;
ll ans;
struct Point{
    int co[2],val;
    Point(){}
    Point(int x,int y,int _val):co{x,y},val(_val){}
    inline bool operator < (const Point &rhs) const
    {
        return co[D]<rhs.co[D];
    }
}pnt[MAXN];
struct node{
    int co[2],x[2],y[2],val,son[2];
    ll sum;
}t[MAXN];
void pushup(int x)
{
    t[x].sum=t[x].val;
    if(ls)
        t[x].sum+=t[ls].sum,
        t[x].x[0]=min(t[x].x[0],t[ls].x[0]),t[x].y[0]=min(t[x].y[0],t[ls].y[0]),
        t[x].x[1]=max(t[x].x[1],t[ls].x[1]),t[x].y[1]=max(t[x].y[1],t[ls].y[1]);
    if(rs)
        t[x].sum+=t[rs].sum,
        t[x].x[0]=min(t[x].x[0],t[rs].x[0]),t[x].y[0]=min(t[x].y[0],t[rs].y[0]),
        t[x].x[1]=max(t[x].x[1],t[rs].x[1]),t[x].y[1]=max(t[x].y[1],t[rs].y[1]);
}
void build(int &x,int l,int r,int d)
{
    if(l>r) return;
    x=++cnt;D=d;
    int mid=(l+r)>>1;
    nth_element(pnt+l,pnt+mid,pnt+r+1);
    t[x].x[0]=t[x].x[1]=t[x].co[0]=pnt[mid].co[0];
    t[x].y[0]=t[x].y[1]=t[x].co[1]=pnt[mid].co[1];
    t[x].val=t[x].sum=pnt[mid].val;
    if(l<mid) build(ls,l,mid-1,d^1);
    if(r>mid) build(rs,mid+1,r,d^1);
    pushup(x);
}
inline int calc(int x,ll a,ll b,ll c)
{
    int ret=0;
    ret+=(a*t[x].x[0]+b*t[x].y[0]<c);
    ret+=(a*t[x].x[1]+b*t[x].y[0]<c);
    ret+=(a*t[x].x[0]+b*t[x].y[1]<c);
    ret+=(a*t[x].x[1]+b*t[x].y[1]<c);
    return ret;
}
void query(int x,ll a,ll b,ll c)
{
    int dl=-1,dr=-1;
    if(a*t[x].co[0]+b*t[x].co[1]<c) ans+=t[x].val;
    if(ls) dl=calc(ls,a,b,c);
    if(rs) dr=calc(rs,a,b,c);
    if(dl==4) ans+=t[ls].sum;
    else if(dl!=-1&&dl!=0) query(ls,a,b,c);
    if(dr==4) ans+=t[rs].sum;
    else if(dr!=-1&&dr!=0) query(rs,a,b,c);
}
int n,m,rt;
ll a,b,c;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&pnt[i].co[0],&pnt[i].co[1],&pnt[i].val);
    build(rt,1,n,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&a,&b,&c);
        ans=0;query(rt,a,b,c);
        printf("%lld\n",ans);
    }
}
