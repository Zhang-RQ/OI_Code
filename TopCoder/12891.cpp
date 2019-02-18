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

class WinterAndSnowmen{
	static const int P=1E9+7;
	static const int MAXN=4100;

	int inc(int x,int y){x+=y;return x>=P?x-P:x;}
	
	int f[2][MAXN][2][2],n,m;

	int solve(int x)
	{
		memset(f,0,sizeof f);
		f[0][0][0][0]=1;
		int lim=max(n,m),lim2=1;
		while(lim2<lim+1) lim2<<=1;
		for(int i=1,nw;i<=lim;i++)
		{
			nw=i&1;memset(f[nw],0,sizeof f[nw]);
			for(int j=0;j<=lim2;j++)
				for(int s1=0;s1<2;s1++)
					for(int s2=0;s2<2;s2++)
					{
						f[nw][j][s1][s2]=inc(f[nw][j][s1][s2],f[!nw][j][s1][s2]);
						if(i<=n) f[nw][j][s1][s2]=inc(f[nw][j][s1][s2],f[!nw][j^i][s1^((i>>x)&1)][s2]);
						if(i<=m) f[nw][j][s1][s2]=inc(f[nw][j][s1][s2],f[!nw][j^i][s1][s2^((i>>x)&1)]);
					}
		}
		int Ans=0;
		for(int j=0;j<=lim2;j++)
			if((j>>(x+1))==0) Ans=inc(Ans,f[lim&1][j][0][1]);
		return Ans;
	}
	
public:
	int getNumber(int N,int M)
	{
		n=N,m=M;
		int lim2=1,lg2=0,Ret=0;
		while(lim2<max(N,M)) lg2++,lim2<<=1;
		for(int i=0;i<=lg2;i++) Ret=inc(Ret,solve(i));
		return Ret;
	}
};
