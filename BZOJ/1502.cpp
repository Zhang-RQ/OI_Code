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
const int MAXN=1010;
const double EPS=1E-7;
double alpha;
int n;
struct circle{
    double x,r;
}p[MAXN];
struct line{
    double k,b,l,r;
}q[MAXN];
double calc(double a,double b){return sqrt(a*a-b*b);}
void get(int x,int y)
{
    if(fabs(p[x].r-p[y].r)<EPS)
    {
        q[x].l=p[x].x;q[x].r=p[y].x;
        q[x].k=0;q[x].b=p[x].r;
        return;
    }
    double dx=p[y].x-p[x].x,dr=fabs(p[x].r-p[y].r),ly,ry;
    if(p[x].r>p[y].r)
    {
        q[x].l=p[x].x+p[x].r*dr/dx;
        q[x].r=p[y].x+(q[x].l-p[x].x)*p[y].r/p[x].r;
        ly=calc(p[x].r,q[x].l-p[x].x);
        ry=calc(p[y].r,q[x].r-p[y].x);
        q[x].k=(ly-ry)/(q[x].l-q[x].r);
        q[x].b=ly-q[x].l*q[x].k;
    }
    else
    {
        q[x].r=p[y].x-p[y].r*dr/dx;
        q[x].l=p[x].x-(p[y].x-q[x].r)*p[x].r/p[y].r;
        ly=calc(p[x].r,q[x].l-p[x].x);
        ry=calc(p[y].r,q[x].r-p[y].x);
        q[x].k=(ly-ry)/(q[x].l-q[x].r);
        q[x].b=ly-q[x].l*q[x].k;
    }
}
double F(double x)
{
    double ret=0;
    for(int i=1;i<=n;i++)
        if(x<p[i].x+p[i].r&&x>p[i].x-p[i].r) 
            ret=max(ret,calc(p[i].r,x-p[i].x));
    for(int i=1;i<=n;i++)
        if(q[i].l<=x&&x<=q[i].r)
            ret=max(q[i].k*x+q[i].b,ret);
    return ret;
}
double Simpson(double l,double r) {return (r-l)*(F(l)+4*F((l+r)/2)+F(r))/6;}
double self_adaptive_Simpson(double L,double R,double ans)
{
    double mid=(L+R)/2.0,lans=Simpson(L,mid),rans=Simpson(mid,R);
    if(fabs(lans+rans-ans)<=EPS) return ans;
    else return self_adaptive_Simpson(L,mid,lans)+self_adaptive_Simpson(mid,R,rans);
}
int main()
{
    scanf("%d%lf",&n,&alpha);
    alpha=1.0/tan(alpha);
    scanf("%lf",&p[1].x);
    p[1].x*=alpha;
    for(int i=2;i<=n+1;i++)
    {
        scanf("%lf",&p[i].x);;
        p[i].x*=alpha;
        p[i].x+=p[i-1].x;
    }
    for(int i=1;i<=n;i++) scanf("%lf",&p[i].r);
    ++n;
    p[n].r=0.0;
    for(int i=1;i<=n-1;i++)
        get(i,i+1);
    double L=p[1].x-p[1].r,R=p[n].x;
    for(int i=1;i<=n;i++) L=min(L,p[i].x-p[i].r),R=max(R,p[i].x+p[i].r);
    printf("%.2lf\n",2*self_adaptive_Simpson(L,R,Simpson(L,R)));
    #ifdef LOCAL
        system("pause");
    #endif
}