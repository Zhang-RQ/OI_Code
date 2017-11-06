#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int INF=0x3f3f3f3f;
const int MAXN=200010;
int n;
struct pnt{
    double x,y;
    bool operator <(pnt a)
    {
        return x==a.x?y<a.y:x<a.x;
    }
}P[MAXN];
static bool cmp1(pnt a,pnt b)
{
    return a.y<b.y;
}
double dis(pnt a,pnt b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double solve(int l,int r)
{
    if(l==r)
        return INF;
    if(l==r-1)
        return dis(P[l],P[r]);
    int mid=(l+r)>>1;
    double ret=min(solve(l,mid),solve(mid+1,r));
    vector<pnt> v;
    for(int i=l;i<=r;i++)
        if(fabs(P[i].x-P[mid].x)<=ret)
            v.push_back(P[i]);
    sort(v.begin(),v.end(),cmp1);
    for(int i=0;i<(signed)v.size();i++)
        for(int j=i+1;j<(signed)v.size();j++)
            if(fabs(v[j].y-v[i].y)<ret)
                ret=min(ret,dis(v[i],v[j]));
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&P[i].x,&P[i].y);
    sort(P+1,P+1+n);
    printf("%.4lf\n",solve(1,n));
}
