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
const int MAXN=1E5+10;
const double EPS=1E-9;
#define X(i) r[i]*f[i]/(r[i]*a[i]+b[i])
#define Y(i) f[i]/(r[i]*a[i]+b[i])
struct P{
    double x,y;
    P(){}
    P(double _x,double _y):x(_x),y(_y){}
    inline bool operator < (const P &rhs) const {return fabs(x-rhs.x)<EPS?y<rhs.y:x<rhs.x;}
    inline double operator * (const P &rhs) const {return (x-rhs.y)*(y-rhs.x);}
    inline P operator - (const P &rhs) const {return P(x-rhs.x,y-rhs.y);}
}stk[MAXN],tp[MAXN];
double f[MAXN],a[MAXN],b[MAXN],r[MAXN];
int n,tmp[MAXN],siz,top,ssiz,s;
inline bool cmp(const int &lhs,const int &rhs){return a[lhs]/b[lhs]>a[rhs]/b[rhs];}
inline double slope(const P &lhs,const P &rhs){return (rhs.y-lhs.y)/(rhs.x-lhs.x+EPS);}
void CDQ(int L,int R)
{
    if(L==R) {f[L]=max(f[L],f[L-1]);return;}
    int mid=(L+R)>>1;
    CDQ(L,mid);ssiz=top=siz=0;
    for(int i=mid+1;i<=R;i++) tmp[++siz]=i;
    sort(tmp+1,tmp+1+siz,cmp);
    for(int i=L;i<=mid;i++) tp[++ssiz]=P(X(i),Y(i));
    sort(tp+1,tp+1+ssiz);
    for(int i=1;i<=ssiz;i++)
    {
        while(top>1&&slope(stk[top],tp[i])+EPS>slope(stk[top-1],stk[top])) --top;
        stk[++top]=tp[i];
    }
    for(int i=1,j=top;i<=siz;i++)
    {
        while(j>1&&slope(stk[j-1],stk[j])<=-a[tmp[i]]/b[tmp[i]]+EPS) j--;
        f[tmp[i]]=max(f[tmp[i]],stk[j].x*a[tmp[i]]+stk[j].y*b[tmp[i]]);
    }
    CDQ(mid+1,R);
}
int main()
{
    scanf("%d%d",&n,&s);f[0]=s;
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&a[i],&b[i],&r[i]);
    CDQ(1,n);
    printf("%.10lf\n",f[n]);
    #ifdef LOCAL
        system("pause");
    #endif
}