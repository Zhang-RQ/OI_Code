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

struct st{
	int v[4][4];
	void print()
	{
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				printf("%d%c",v[i][j],j==3?'\n':' ');
		puts("");
	}
	inline st rot()
	{
		st ret;
		ret.v[1][1]=v[2][1];ret.v[1][2]=v[1][1];ret.v[1][3]=v[1][2];
		ret.v[2][1]=v[3][1];ret.v[2][2]=v[2][2];ret.v[2][3]=v[1][3];
		ret.v[3][1]=v[3][2];ret.v[3][2]=v[3][3];ret.v[3][3]=v[2][3];
		return ret;
	}
	inline st Shift()
	{
		st ret;
		ret.v[1][1]=v[1][1];ret.v[1][2]=v[1][2];ret.v[1][3]=v[1][3];
		ret.v[2][1]=v[2][3];ret.v[2][2]=v[2][1];ret.v[2][3]=v[2][2];
		ret.v[3][1]=v[3][1];ret.v[3][2]=v[3][2];ret.v[3][3]=v[3][3];
		return ret;
	}
	bool operator == (const st &rhs) const
	{
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				if(v[i][j]!=rhs.v[i][j])
					return 0;
		return 1;
	}
	bool operator < (const st &rhs) const
	{
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				if(v[i][j]<rhs.v[i][j])
					return 1;
				else if(v[i][j]>rhs.v[i][j])
					return 0;
		return 0;
	}
}now,dst;

map<st,st> pre;
vector<st> Ans;

int bfs()
{
	queue<pair<st,int> > q;
	q.push({now,1});
	while(!q.empty())
	{
		auto x=q.front();q.pop();
		if(x.first==dst) return x.second;
		st tmp=x.first.rot();
		if(pre.find(tmp)==pre.end())
			q.push({tmp,x.second+1}),pre[tmp]=x.first;
		tmp=x.first.Shift();
		if(pre.find(tmp)==pre.end())
			q.push({tmp,x.second+1}),pre[tmp]=x.first;
	}
	return -1;
}

int main()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			dst.v[i][j]=(i-1)*3+j-1;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			scanf("%d",&now.v[i][j]);
	int Res=bfs();
	if(Res==-1) return puts("UNSOLVABLE"),0;
	printf("%d\n",Res-1);
	st t=dst;
	while(!(t==now))
		Ans.push_back(t),t=pre[t];
	Ans.push_back(now);
	reverse(Ans.begin(),Ans.end());
	for(st v:Ans)
		v.print();
}