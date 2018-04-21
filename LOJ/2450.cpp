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
struct Point{
    int x,y;
    Point(){}
    Point(int _x,int _y){x=_x;y=_y;}
    inline Point operator - (const Point &rhs) const {return Point(x-rhs.x,y-rhs.y);}
    inline int operator *  (const Point &rhs) const {return x*rhs.y-y*rhs.x;}
}now,farm[601],shep[20010];
int n,k,mod;
int f[601][601];
bool ok[601][601];
inline bool cmp(const Point &lhs,const Point &rhs) {return (lhs-now)*(rhs-now)<0;}
int dfs(int l,int r)
{
    if(f[l][r]!=-1) return f[l][r];
    int &res=f[l][r];
    res=0;
    for(int i=l+1;i<r;i++)
    {
        if(ok[l][i]&&ok[i][r])
            res=(res+1LL*dfs(l,i)*dfs(i,r))%mod;
    }
    return res;
}
void pre()
{
    now=farm[1];sort(farm+2,farm+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        now=farm[i];sort(shep+1,shep+1+k,cmp);
        int res=0;
        for(int j=i+1;j<=n;j++)
        {
            while(res<k&&(shep[res+1]-now)*(farm[j]-now)<0) ++res;
            if(res&1||(shep[res+1]-now)*(farm[j]-now)==0) continue;
            ok[i][j]=ok[j][i]=true;
        }
    }
}
int main()
{
    memset(f,-1,sizeof f);
    scanf("%d%d%d",&n,&k,&mod);
    for(int i=1;i<=n;i++) scanf("%d%d",&farm[i].x,&farm[i].y);
    for(int i=1;i<=k;i++) scanf("%d%d",&shep[i].x,&shep[i].y);
    pre();
    for(int i=1;i<n;i++) f[i][i+1]=1;
    printf("%d\n",dfs(1,n));
}
