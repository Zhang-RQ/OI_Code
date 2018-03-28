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
#define mxn 20005
struct pnt{double x,y;};
struct line{
    double a,b,c,k;
    int id;
    line(){}
    line(double va,double vb,double vc,int ID)
    {
        a=va,b=vb,c=vc,k=atan2(-a,b),id=ID;
        double tmp=fabs(va);
        if(tmp>0) a/=tmp,b/=tmp,c/=tmp;
    }
    inline bool operator < (const line &l) const
    {
        if(k==l.k) return c<l.c;
        return k<l.k;
    }
}q[mxn],ln[mxn];
inline pnt its(line a,line b)
{
    return (pnt){(a.b*b.c-b.b*a.c)/(a.a*b.b-b.a*a.b),(a.a*b.c-b.a*a.c)/(b.a*a.b-a.a*b.b)};
}
inline bool judge(line l,pnt p){return l.a*p.x+l.b*p.y+l.c<=0;}
int qh,qt;
inline void HPI(line *l,int cnt)
{
    qh=qt=1,q[1]=l[1];
    for(int i=2;i<=cnt;++i)
    {
        while(qh<qt&&judge(l[i],its(q[qt],q[qt-1]))) --qt;
        while(qh<qt&&judge(l[i],its(q[qh],q[qh+1]))) ++qh;
        q[++qt]=l[i];
    }
    while(qh<qt&&judge(q[qh],its(q[qt],q[qt-1]))) --qt;
}
int n,a[mxn],b[mxn],c[mxn],tot;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d%d%d",&a[i],&b[i],&c[i]);
    for(int i=1;i<=n;++i)
    {
        double x,y,z;
        tot=0;
        ln[++tot]=line(1,0,0,-1),ln[++tot]=line(0,1,0,-2),ln[++tot]=line(-1,-1,1,-3);
        for(int j=1;j<=n;++j) if(i!=j)
        {
            x=1.0/a[i]-1.0/a[j]-1.0/c[i]+1.0/c[j];
            y=1.0/b[i]-1.0/b[j]-1.0/c[i]+1.0/c[j];
            z=1.0/c[i]-1.0/c[j];
            x*=-1,y*=-1,z*=-1;
            ln[++tot]=line(x,y,z,j);
        }
        sort(&ln[1],&ln[tot+1]);
        int cnt=1;
        for(int j=2;j<=tot;++j) if(ln[j].k>ln[cnt].k) ln[++cnt]=ln[j];
        HPI(ln,cnt);
        puts(qt-qh>1?"Yes":"No");
    }
}
