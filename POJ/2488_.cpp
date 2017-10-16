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
int mv[10][10]={
	{-1,-2},
	{ 1,-2},
	{-2,-1},
	{ 2,-1},
	{-2, 1},
	{ 2, 1},
	{-1, 2},
	{ 1, 2}
};
int n,m;
bool vis[50][50];
inline bool inside(int x,int y)
{
    return 1<=x&&x<=n&&1<=y&&y<=m;
}
vector<pair<int,int> > path;
bool dfs(int x,int y,int step)
{
    int _x,_y;
    vis[x][y]=1;
	if(step<=(signed)path.size()) path[step-1]=make_pair(x,y);
	else path.push_back(make_pair(x,y));
	if(step==n*m)
		return 1;
    for(int i=0;i<8;i++)
    {
        _x=x+mv[i][0];
        _y=y+mv[i][1];
        if(inside(_x,_y)&&!vis[_x][_y]&&dfs(_x,_y,step+1))
			return 1;
    }
	vis[x][y]=0;
	return 0;
}
int main()
{
	int T,T_;
	scanf("%d",&T);
	for(T_=1;T_<=T;T_++)
	{
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		path.clear();
		printf("Scenario #%d:\n",T_);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(dfs(i,j,1))
				{
					for(int k=0;k<(signed)path.size();k++)
					{
						int x=path[k].first,y=path[k].second;
						putchar('A'-1+y);
						printf("%d",x);
					}
					printf("\n");
					goto nxt;
				}
		printf("impossible\n");
		nxt:;
	}
}
