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
int path[300][2];
int tx,ty,sx,sy,m,n;
int mp[30][30];
int vis[30][30];
bool flag=0;
void print_ans(int len)
{
    for(int i=0;i<len;i++)
        printf("(%d,%d)->",path[i][0],path[i][1]);
    printf("(%d,%d)\n",path[len][0],path[len][1]);
}
bool ok(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&!vis[x][y]&&mp[x][y];
}
void dfs(int x,int y,int cur) //当前要走第cur步
{
    if(x==tx&&y==ty)
    {
        print_ans(cur-1);
        flag=1;
        return;
    }
    if(ok(x-1,y))
    {
        vis[x-1][y]=1;
        path[cur][0]=x-1;
        path[cur][1]=y;
        dfs(x-1,y,cur+1);
        vis[x-1][y]=0;
    }
    if(ok(x,y-1))
    {
        vis[x][y-1]=1;
        path[cur][0]=x;
        path[cur][1]=y-1;
        dfs(x,y-1,cur+1);
        vis[x][y-1]=0;
    }
    if(ok(x,y+1))
    {
        vis[x][y+1]=1;
        path[cur][0]=x;
        path[cur][1]=y+1;
        dfs(x,y+1,cur+1);
        vis[x][y+1]=0;
    }
    if(ok(x+1,y))
    {
        vis[x+1][y]=1;
        path[cur][0]=x+1;
        path[cur][1]=y;
        dfs(x+1,y,cur+1);
        vis[x+1][y]=0;
    }
}
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            cin>>mp[i][j];
    cin>>sx>>sy;
    cin>>tx>>ty;
    path[0][0]=sx;
    path[0][1]=sy;
    vis[sx][sy]=1;
    dfs(sx,sy,1);
    if(!flag)
        puts("-1");
}
