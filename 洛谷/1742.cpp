#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const double EPS=1E-12;

struct vec{
    double x,y;

    vec(double _x=0,double _y=0) {x=_x;y=_y;}
    vec operator + (const vec &rhs) const {return vec(x+rhs.x,y+rhs.y);}
    vec operator - (const vec &rhs) const {return vec(x-rhs.x,y-rhs.y);}
    vec operator * (const double &rhs) const {return vec(x*rhs,y*rhs);}
    vec operator / (const double &rhs) const {return vec(x/rhs,y/rhs);}
    friend vec turn_90d(const vec &v){return vec(v.y,-v.x);}//clockwise
    friend double dis(const vec &v1,const vec &v2) {return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y));}
    friend double dis2(const vec &v1,const vec &v2) {return (v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y);}
    friend double dot(const vec &lhs,const vec &rhs) {return lhs.x*rhs.x+lhs.y*rhs.y;}
    friend double cross(const vec &lhs,const vec &rhs){return lhs.x*rhs.y-lhs.y*rhs.x;}
}P[MAXN];

ostream& operator << (ostream& out,vec v)
{
    out<<"("<<v.x<<","<<v.y<<")";
    return out;
}

int n;

struct Line{
    vec p,v;
    
    Line(vec _p=vec(),vec _v=vec()){p=_p;v=_v;}
    friend vec intersect(const Line &l,const Line &r)
    {
        double t1=cross(r.p-l.p,r.v),t2=cross(l.v,r.v);
        t1/=t2;
        return l.p+l.v*t1;
    }
};

ostream& operator << (ostream& out,Line l)
{
    out<<"{p="<<l.p<<","<<"v="<<l.v<<"}";
    return out;
}

pair<vec,double> get_circle(vec p1,vec p2,vec p3)
{
    Line l1=Line((p1+p2)/2,turn_90d(p2-p1)),l2=Line((p1+p3)/2,turn_90d(p3-p1));
    vec p=intersect(l1,l2);
    return make_pair(p,dis2(p,p1));
}

int main()
{
    srand((ull)new char);
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>P[i].x>>P[i].y;
    random_shuffle(P+1,P+1+n);
    pair<vec,double> C={P[0],0};
    for(int i=1;i<=n;i++)
    {
        if(dis2(C.first,P[i])>C.second)
        {
            C={P[i],0};
            for(int j=1;j<i;j++)
                if(dis2(C.first,P[j])>C.second)
                {
                    C={(P[i]+P[j])/2,dis2(P[i],P[j])/4};
                    for(int k=1;k<j;k++)
                        if(dis2(C.first,P[k])>C.second)
                            C=get_circle(P[i],P[j],P[k]);
                }
        }
    }
    cout<<fixed<<setprecision(10)<<sqrt(C.second)<<endl;
    cout<<C.first.x<<" "<<C.first.y<<endl;
}