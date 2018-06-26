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

const int MAXN=100010;

struct Point{
    int x,y,id;
    Point(){}
    Point(int _x,int _y,int _id){x=_x;y=_y;id=_id;}
    inline bool operator < (const Point &rhs) const
    {
        if(y!=rhs.y) return y<rhs.y;
        return x<rhs.x;
    }
}pnt[MAXN];

bool cmp(const Point &lhs,const Point &rhs) {return lhs.x<rhs.x;}

int n,fa[MAXN],siz[MAXN],pt,c,ans1,ans2;
set<Point> s;
set<Point>::iterator it1,it2;

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

inline void merge(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    if(siz[x]<siz[y]) swap(x,y);
    fa[y]=x;siz[x]+=siz[y];
}

int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1,x,y;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        pnt[i]=Point(x+y,x-y,i);
        fa[i]=i;siz[i]=1;
    }
    sort(pnt+1,pnt+1+n,cmp);
    pt=1;s.insert(pnt[1]);
    for(int i=2;i<=n;i++)
    {
        while(pnt[i].x-pnt[pt].x>c) s.erase(pnt[pt++]);
        it1=it2=s.insert(pnt[i]).first;
        if(it1!=s.begin()) if(abs((--it1)->y-pnt[i].y)<=c)merge(it1->id,pnt[i].id);
        if((++it2)!=s.end()) if(abs(it2->y-pnt[i].y)<=c) merge(it2->id,pnt[i].id);
    }
    for(int i=1;i<=n;i++)
        if(fa[i]==i) ++ans1,ans2=max(ans2,siz[i]);
    printf("%d %d\n",ans1,ans2);
    #ifdef LOCAL
        system("pause");
    #endif
}