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

const int mv[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};

struct st{
	int v[6][6],x,y,dlt,stp;
	int* operator [](int i){return v[i];}
	const int* operator [](int i)const{return v[i];}
	bool operator < (const st &rhs) const {return dlt+stp<rhs.dlt+rhs.stp;}
	bool operator == (const st &rhs) const
	{
		for(int i=1;i<=5;i++)
			for(int j=1;j<=5;j++)
				if(v[i][j]!=rhs[i][j])
					return 0;
		return 1;
	}
	void print()
	{
		for(int i=1;i<=5;i++)
			for(int j=1;j<=5;j++)
				printf("%d%c",v[i][j],j==5?'\n':' ');
		puts("");
	}
}dst,be;

int Ans=-1,Lim;
char mp[6][6];

inline void calc_diff(st &rhs)
{
	rhs.dlt=0;
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			rhs.dlt+=dst[i][j]!=rhs[i][j];
}

void IDAstar(st s)
{
	if(s.dlt==0){return Ans=s.stp,void();}
	if(Ans!=-1) return;
	for(int i=0;i<8;i++)
	{
		int tx=mv[i][0]+s.x,ty=mv[i][1]+s.y;
		if(tx<1||tx>5||ty<1||ty>5) continue;
		swap(s[s.x][s.y],s[tx][ty]);swap(tx,s.x);swap(ty,s.y);
		calc_diff(s);s.stp++;
		if(s.stp+s.dlt>Lim)
		{
			swap(s[s.x][s.y],s[tx][ty]);swap(tx,s.x);swap(ty,s.y);
			s.stp--;
			continue;
		}
		IDAstar(s);
		swap(s[s.x][s.y],s[tx][ty]);swap(tx,s.x);swap(ty,s.y);
		s.stp--;
	}
}

void solve()
{
	for(int i=1;i<=5;i++)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=5;j++)
			if(mp[i][j]!='*')
				be[i][j]=mp[i][j]-'0';
			else be[i][j]=2,be.x=i,be.y=j;
	}
	Ans=-1;calc_diff(be);
	for(int i=1;i<=16;i++)
	{
		Lim=i;
		IDAstar(be);
		if(Ans!=-1) break;
	}
	printf("%d\n",Ans);
}

int main()
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			if(j>=i+(i>2))
				dst[i][j]=1;
			else dst[i][j]=0;
	dst[3][3]=2;
	int T;
	for(scanf("%d",&T);T--;solve());
}