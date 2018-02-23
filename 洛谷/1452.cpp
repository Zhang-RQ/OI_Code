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
const int MAXN=50010;
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
}pnt[MAXN],stk[MAXN];
inline double dis(Point a,Point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
bool cmp(Point a,Point b)
{
    double m=(a-pnt[1])*(b-pnt[1]);
    if(fabs(m)<eps) return dis(a,pnt[1])<dis(b,pnt[1]);
    return m>0;
}
int n,top;
void get()
{
    top=0;
    int fir=0;
    pnt[fir]=Point(1000000,1000000);
    for(int i=1;i<=n;i++)
        if(pnt[i].y<pnt[fir].y||(fabs(pnt[i].y-pnt[fir].y)<eps&&pnt[i].x<pnt[fir].x))
            fir=i;
    swap(pnt[1],pnt[fir]);
    sort(pnt+2,pnt+1+n,cmp);
    stk[++top]=pnt[1];stk[++top]=pnt[2];
    for(int i=3;i<=n;i++)
    {
        while(top>1&&(pnt[i]-stk[top-1])*(stk[top]-stk[top-1])>=0)
            --top;
        stk[++top]=pnt[i];
    }
}
double calc_ans()
{
    double ret=0;
    if(n==2) return dis(stk[1],stk[2]);
    stk[++top]=stk[1];
    int j=3;
    for(int i=1;i<top;i++)
    {
        while((stk[i+1]-stk[i])*(stk[j]-stk[i])<(stk[i+1]-stk[i])*(stk[j+1]-stk[i]))
            j=(j+1)%top+1;
        ret=max(ret,max(dis(stk[i],stk[j]),dis(stk[i+1],stk[j])));
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&pnt[i].x,&pnt[i].y);
    get();
    printf("%.0lf\n",calc_ans());
}
