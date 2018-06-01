#include<cstdio>
#include<cmath>
const double EPS=1E-9;
double a;
inline double f(double x) {return pow(x,a/x-x);}
inline double Simpson(double L,double R) {return (R-L)*(f(L)+4.0*f((L+R)/2.0)+f(R))/6.0;}
double self_adaptive_Simpson(double L,double R,double ans)
{
    double mid=(L+R)/2.0,lans=Simpson(L,mid),rans=Simpson(mid,R);
    if(fabs(lans+rans-ans)<=EPS) return ans;
    else return self_adaptive_Simpson(L,mid,lans)+self_adaptive_Simpson(mid,R,rans);
}
int main()
{
    scanf("%lf",&a);
    if(a<0) {puts("orz");return 0;}
    printf("%.5lf\n",self_adaptive_Simpson(EPS,20,Simpson(EPS,20)));
}