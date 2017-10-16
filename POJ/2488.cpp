#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

int T,n,m,vis[50][50],del[10][10]={
	{-1,-2},
	{ 1,-2},
	{-2,-1},
	{ 2,-1},
	{-2, 1},
	{ 2, 1},
	{-1, 2},
	{ 1, 2}
};

vector<pair<int,int> > path;

inline bool inside(int x,int y)
{
	return 1<=x&&x<=n&&1<=y&&y<=m;
}

bool dfs(int x,int y,int step)
{
	vis[x][y]=1;
	if((signed)path.size()>=step)
		path[step-1]=make_pair(x,y);
	else
		path.push_back(make_pair(x,y));
	if(step==n*m) return 1;
	for(int i=0;i<8;i++)
    {
		int x_=x+del[i][0],y_=y+del[i][1];
		if(inside(x_,y_)&&!vis[x_][y_]&&dfs(x_,y_,step+1))
			return 1;
	}
	vis[x][y]=0;
	return 0;
}

int main()
{
	scanf("%d",&T);
	for(int T_=1;T_<=T;T_++)
    {
		memset(vis,0,sizeof(vis));
		path.clear();
		scanf("%d%d",&n,&m);
		printf("Scenario #%d:\n",T_);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
            {
				if(dfs(i,j,1))
                {
					for(int i=0;i<(signed)path.size();i++)
                    {
						int x=path[i].first,y=path[i].second;
						putchar('A'+y-1);
						printf("%d",x);
					}
					puts("\n");
					goto nxt;
				}
			}
		puts("impossible\n");
		nxt:;
	}
}
