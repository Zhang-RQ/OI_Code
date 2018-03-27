// luogu-judger-enable-o2
%:pragma GCC optimize(2)
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
#define double long double
const int MAXN=200010;
const double eps=1e-18,INF=1e15;
struct P{
    double x,y;
    P(double _x=0,double _y=0){x=_x;y=_y;}
    inline P operator -(const P &rhs)const{return P(x-rhs.x,y-rhs.y);}
    inline double operator * (const P &rhs)const{return x*rhs.y-y*rhs.x;}
};
struct L{
    P a,b;
    double slope;
    L(P _a=P(),P _b=P()) {a=_a,b=_b;}
    inline bool operator < (const L &rhs)const
    {
        return fabs(slope-rhs.slope)<eps?((rhs.b-a)*(b-a))>0:slope<rhs.slope;
    }
    inline friend P inter(L x,L y)
    {
        double c1=(x.a-y.a)*(y.b-y.a),c2=(y.b-y.a)*(x.b-y.a);
        return P((x.a.x*c2+x.b.x*c1)/(c1+c2),(x.a.y*c2+x.b.y*c1)/(c1+c2));
    }
    inline friend P inters(L x,L y){
        P ans;
        double c1=(x.a-y.a)*(y.b-y.a),c2=(y.b-y.a)*(x.b-y.a);
        ans.x=(x.a.x*c2+x.b.x*c1)/(c1+c2),ans.y=(x.a.y*c2+x.b.y*c1)/(c1+c2);
        return ans;
    }
}q[MAXN],ls[MAXN],ls2[MAXN];
int x[MAXN],y[2][MAXN],n;
bool lineR(L x,P a) {return (x.b-x.a)*(a-x.a)<0;}
bool check(int mid)
{
    int cnt=0,l=1,r=0,rcnt=0;
    ls[++cnt]=L(P(INF,INF),P(-INF,INF));
    ls[++cnt]=L(P(-INF,INF),P(-INF,-INF));
    ls[++cnt]=L(P(-INF,-INF),P(INF,-INF));
    ls[++cnt]=L(P(INF,-INF),P(INF,INF));
    for(int i=1;i<=mid;i++)
    {
        ls[++cnt]=L(P(-1,x[i]+1.0*y[0][i]/x[i]),P(1,1.0*y[0][i]/x[i]-x[i]));
        ls[++cnt]=L(P(1,1.0*y[1][i]/x[i]-x[i]),P(-1,x[i]+1.0*y[1][i]/x[i]));
    }
    for(int i=1;i<=cnt;i++)
        ls[i].slope=atan2(ls[i].b.y-ls[i].a.y,ls[i].b.x-ls[i].a.x);
    sort(ls+1,ls+1+cnt);
    for(int i=1;i<=cnt;i++)
    {
        if(i>1&&ls[i].slope==ls[i-1].slope)  continue;
        ls2[++rcnt]=ls[i];
    }
    q[++r]=ls2[1];q[++r]=ls2[2];
    for(int i=3;i<=rcnt;i++)
    {
        while(l<r&&lineR(ls2[i],inter(q[r-1],q[r])))
            r--;
        while(l<r&&lineR(ls2[i],inter(q[l],q[l+1])))
            l++;
        q[++r]=ls2[i];
    }
    while(l<r&&lineR(q[l],inter(q[r-1],q[r]))) r--;
    while(l<r&&lineR(q[r],inter(q[l],q[l+1]))) l++;
    return r-l>=2;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&x[i],&y[0][i],&y[1][i]);
    int L=1,R=n,ans=0;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(check(mid)) ans=mid,L=mid+1;
        else R=mid-1;
    }
    printf("%d\n",ans);
}
