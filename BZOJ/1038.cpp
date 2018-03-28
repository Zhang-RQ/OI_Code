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
const double INF=1E15,eps=1e-5;
const int MAXN=10010;
struct P{
    double x,y;
    P(){}
    P(double _x,double _y){x=_x;y=_y;}
    inline P operator + (const P &rhs) const {return P(x+rhs.x,y+rhs.y);}
    inline P operator - (const P &rhs) const {return P(x-rhs.x,y-rhs.y);}
    inline double operator * (const P &rhs) const {return x*rhs.y-y*rhs.x;}
    inline bool operator < (const P &rhs) const{return x<rhs.x;}
}pnt[MAXN];
struct L{
    P a,b;
    double k;
    L(){}
    L(P _a,P _b){a=_a;b=_b;k=atan2(b.y-a.y,b.x-a.x);}
    inline bool operator < (const L &rhs) {return fabs(k-rhs.k)<eps?(rhs.a-a)*(rhs.b-a)<-eps:k<rhs.k;}
    inline friend P inter(L a,L b)
    {
        double c1=(b.b-a.a)*(b.a-a.a),c2=(b.a-a.b)*(b.b-a.b);
        return P(a.a.x+(a.b.x-a.a.x)*(c1/(c1+c2)),a.a.y+(a.b.y-a.a.y)*(c1/(c1+c2)));
    }
}q[MAXN],ls[MAXN],res[MAXN];
inline bool cmp(L a,L b){return a.a<b.a;}
bool lineL(L a,P x) {return (a.b-x)*(a.a-x)<eps;}
int n,tot,cnt,l,r;
void HPI()
{
    sort(ls+1,ls+1+tot);
    l=1,r=0;q[++r]=ls[1];q[++r]=ls[2];
    for(int i=3;i<=tot;i++)
    {
        while(l<r&&!lineL(ls[i],inter(q[r-1],q[r]))) r--;
        while(l<r&&!lineL(ls[i],inter(q[l],q[l+1]))) l++;
        q[++r]=ls[i];
    }
    while(l<r&&!lineL(q[l],inter(q[r-1],q[r]))) r--;
    while(l<r&&!lineL(q[r],inter(q[l],q[l+1]))) l++;
    // for(int i=l;i<=r;i++)   printf("(%lf,%lf)->(%lf,%lf)\n",q[i].a.x,q[i].a.y,q[i].b.x,q[i].b.y);
}
inline double geth(double x) //下
{
    if(x<pnt[1].x||x>pnt[n].x) return 0;
    for(int i=1;i<n;i++)
        if(pnt[i].x<=x&&x<=pnt[i+1].x)
        {
            double a=x-pnt[i].x,b=pnt[i+1].x-pnt[i].x;
            return pnt[i].y+(pnt[i+1].y-pnt[i].y)*(a/b);
        }
    return 0;
}
inline double gety(double x) // 半平面交
{
    L tp(P(x,-INF),P(x,INF));
    double ret=-INF;
    for(int i=1;i<=cnt;i++)  ret=max(ret,inter(tp,res[i]).y);
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf",&pnt[i].x);
    for(int i=1;i<=n;i++)
        scanf("%lf",&pnt[i].y);
    sort(pnt+1,pnt+1+n);
    for(int i=1;i<n;i++) ls[++tot]=L(pnt[i],pnt[i+1]);
    HPI();
    double ans=2e18;
    for(int i=l;i<=r;i++) res[++cnt]=q[i];
    for(int i=1;i<cnt;i++)
    {
        bool ok=1;
        P tp=inter(res[i],res[i+1]);
        for(int j=1;j<=cnt;j++) if(!lineL(res[j],tp)) {ok=0;break;}
        if(ok) ans=min(ans,tp.y-geth(tp.x));
    }
    sort(res+1,res+1+cnt,cmp);
    for(int i=1;i<=n;i++) ans=min(ans,gety(pnt[i].x)-pnt[i].y);
    printf("%.3lf\n",ans);
}
