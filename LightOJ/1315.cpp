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
const int mv[6][2]={
    {-2, 1},
    {-3,-1},
    {-2,-1},
    {-1,-2},
    {-1,-3},
    { 1,-2}
};
bool check(int x,int y)  {return 0<=x&&0<=y;}
int sg[1010][1010],T,n,x,y,Cs;
bool vis[1010][1010];
ll ans=0;
void dfs(int x,int y)
{
    assert(x>=0);assert(y>=0);
    if(vis[x][y]) return;
    vis[x][y]=1;
    bool vs[10]={0};
    for(int i=0;i<6;i++)
    {
        int _x=x+mv[i][0],_y=y+mv[i][1];
        if(!check(_x,_y)) continue;
        dfs(_x,_y);
        assert(sg[_x][_y]<10);
        vs[sg[_x][_y]]=1;
    }
    for(int i=0;i<10;i++)
        if(!vs[i]) {sg[x][y]=i;break;}
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans=0;
        while(n--) scanf("%d%d",&x,&y),dfs(x,y),ans^=sg[x][y];
        printf("Case %d: ",++Cs);
        puts(ans?"Alice":"Bob");
    }
}
