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
const int MAXN=50010;
int globalx,n,tot,dep[MAXN];
struct Circle{
    int x,y,r;
}cir[MAXN];
struct Event{
    int x,f,id;
    Event(){}
    Event(int _x,int _f,int _id):x(_x),f(_f),id(_id){}
    inline bool operator < (const Event &rhs) const {return x<rhs.x;} 
}eve[MAXN<<1];
double get_ins(int id,int ty)
{
    double t=sqrt(1.0*cir[id].r*cir[id].r-(1.0*globalx-cir[id].x)*(1.0*globalx-cir[id].x));
    if(ty) return cir[id].y+t;
    else return cir[id].y-t;
}
struct Point{
    int id,ty;//ty=0 down,ty=1 up
    Point(){}
    Point(int _id,int _ty):id(_id),ty(_ty){}
    inline bool operator < (const Point &rhs) const
    {
        if(id==rhs.id) return ty>rhs.ty;
        return get_ins(id,ty)>get_ins(rhs.id,rhs.ty);
    }
};
set<Point> s;
int main()
{
    while(~scanf("%d",&n))
    {
        tot=0;memset(dep,0,sizeof dep);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&cir[i].x,&cir[i].y,&cir[i].r),
            eve[++tot]=Event(cir[i].x-cir[i].r,1,i),
            eve[++tot]=Event(cir[i].x+cir[i].r,-1,i);
        sort(eve+1,eve+1+tot);
        set<Point>::iterator it1,it2;
        for(int i=1;i<=tot;i++)
        {
            globalx=eve[i].x;
            if(eve[i].f==1)
            {
                it1=it2=s.insert(Point(eve[i].id,1)).first;
                ++it2;
                if(it2==s.end()||it1==s.begin())
                    dep[eve[i].id]=1;
                else
                {
                    --it1;
                    if(it1->id==it2->id) dep[eve[i].id]=dep[it1->id]+1;
                    else if(dep[it1->id]==dep[it2->id]) dep[eve[i].id]=dep[it1->id];
                    else dep[eve[i].id]=max(dep[it1->id],dep[it2->id]);
                }
                s.insert(Point(eve[i].id,0));
            }
            else
            {
                s.erase(Point(eve[i].id,1));s.erase(Point(eve[i].id,0));
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++) ans=max(ans,dep[i]);
        printf("%d\n",ans);
    }
    #ifdef LOCAL
        system("pause");
    #endif
}