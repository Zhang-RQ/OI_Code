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
const double EPS=1E-9;
double a,b,c,d,l,r;
inline double f(double x){return (c*x+d)/(a*x+b);}
inline double Simpson(double L,double R)
{
    double mid=(L+R)/2;
    return (R-L)*(f(L)+4*f(mid)+f(R))/6;
}
double self_adaptive_Simpson(double L,double R)
{
    double mid=(L+R)/2;
    if(fabs(Simpson(L,mid)+Simpson(mid,R)-Simpson(L,R))<EPS) return Simpson(L,R);
    return self_adaptive_Simpson(L,mid)+self_adaptive_Simpson(mid,R);
}
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&l,&r);
    printf("%.6lf\n",self_adaptive_Simpson(l,r));
    #ifdef LOCAL
        system("pause");
    #endif
}