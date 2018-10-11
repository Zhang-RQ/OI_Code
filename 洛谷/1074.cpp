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

const int mp[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,6,6,6,6,6,6,6,6,6},
	{0,6,7,7,7,7,7,7,7,6},
	{0,6,7,8,8,8,8,8,7,6},
	{0,6,7,8,9,9,9,8,7,6},
	{0,6,7,8,9,10,9,8,7,6},
	{0,6,7,8,9,9,9,8,7,6},
	{0,6,7,8,8,8,8,8,7,6},
	{0,6,7,7,7,7,7,7,7,6},
	{0,6,6,6,6,6,6,6,6,6}
};

const int bl[10][10]={
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,2,2,2,3,3,3},
	{0,1,1,1,2,2,2,3,3,3},
	{0,1,1,1,2,2,2,3,3,3},
	{0,4,4,4,5,5,5,6,6,6},
	{0,4,4,4,5,5,5,6,6,6},
	{0,4,4,4,5,5,5,6,6,6},
	{0,7,7,7,8,8,8,9,9,9},
	{0,7,7,7,8,8,8,9,9,9},
	{0,7,7,7,8,8,8,9,9,9},
};

int blk[10],ln[10],rw[10],cnt,rst[10];
int rAns,Ans=-1;

struct Point{
	int x,y,l;
	Point(int _x=0,int _y=0,int _l=0){x=_x;y=_y;l=_l;}
	bool operator < (const Point &rhs) const
	{
		return rst[x]<rst[rhs.x];
	}
}pnt[60];

void dfs(int x,int cur)
{
	if(x>cnt) return Ans=max(Ans,cur),void();
	int s=ln[pnt[x].x]&rw[pnt[x].y]&blk[bl[pnt[x].x][pnt[x].y]];
	for(int i=9;i>=1;i--)
		if((s>>i)&1)
		{
			ln[pnt[x].x]^=1<<i;
			rw[pnt[x].y]^=1<<i;
			blk[bl[pnt[x].x][pnt[x].y]]^=1<<i;
			dfs(x+1,cur+i*pnt[x].l);
			ln[pnt[x].x]^=1<<i;
			rw[pnt[x].y]^=1<<i;
			blk[bl[pnt[x].x][pnt[x].y]]^=1<<i;
		}
}

int main()
{
	for(int i=1;i<=9;i++)
		ln[i]=((1<<9)-1)<<1,
		rw[i]=((1<<9)-1)<<1,
		blk[i]=((1<<9)-1)<<1;
	for(int i=1,x;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			scanf("%d",&x);
			if(!x) pnt[++cnt]=Point(i,j,mp[i][j]);
			else 
			{
				if(!((ln[i]>>x)&1)) return puts("-1"),0;
				if(!((rw[j]>>x)&1)) return puts("-1"),0;
				if(!((blk[bl[i][j]]>>x)&1)) return puts("-1"),0;
				rAns+=x*mp[i][j],ln[i]^=1<<x,rw[j]^=1<<x,blk[bl[i][j]]^=1<<x;
				rst[i]--;
			}
		}
	sort(pnt+1,pnt+1+cnt);
	dfs(1,0);
	if(Ans==-1) return puts("-1"),0;
	printf("%d\n",Ans+rAns);
}