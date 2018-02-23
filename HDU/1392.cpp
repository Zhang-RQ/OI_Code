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
const int MAXN=11000;
const int INF=1<<30;
const double eps=1e-6;
struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    inline friend Point operator - (const Point &a,const Point &b)
    {
        return Point(a.x-b.x,a.y-b.y);
    }
    inline friend double operator * (const Point &a,const Point &b)
    {
        return a.x*b.y-b.x*a.y;
    }
    inline friend bool operator == (const Point &a,const Point &b)
    {
        return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
    }
}pnt[MAXN];
Point stk[MAXN];
int top;
double dis(Point a,Point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
int n;
bool cmp(Point a,Point b)
{
    double m=(a-pnt[1])*(b-pnt[1]);
    if(fabs(m)<eps) return dis(a,pnt[1])<dis(b,pnt[1]);
    return m>0;
}
void get()
{
    top=0;
    int fir=0;
    pnt[fir]=Point(INF,INF);
    for(int i=1;i<=n;i++)
        if(pnt[fir].y>pnt[i].y||(fabs(pnt[fir].y-pnt[i].y)<eps&&pnt[i].x<pnt[fir].x))
            fir=i;
    swap(pnt[1],pnt[fir]);
    sort(pnt+2,pnt+1+n,cmp);
    stk[++top]=(pnt[1]);stk[++top]=(pnt[2]);
    for(int i=3;i<=n;i++)
    {
        while(top>2&&(pnt[i]-stk[top])*(pnt[top]-stk[top-1])>=0)
            top--;
        stk[++top]=pnt[i];
    }
}
double calc_ans()
{
    if(n==1) return 0.0;
    if(n==2) return sqrt(dis(stk[1],stk[2]));
    double ret=0;
    for(int i=2;i<=top;i++) ret+=sqrt(dis(stk[i-1],stk[i]));
    ret+=sqrt(dis(stk[1],stk[top]));
    return ret;
}
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        for(int i=1;i<=n;i++) scanf("%lf%lf",&pnt[i].x,&pnt[i].y);
        get();
        printf("%.2lf\n",calc_ans());
    }
}
