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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=610;
const int MAXR=505;

bitset<MAXR> f[MAXN][5010];

int D,S,pw[MAXN];

void dfs(int x,int s,int r,bool fir)
{
	if(x==0) return;
	for(int i=fir;i<=9;i++)
		if(f[x-1][s-i][(r-pw[x-1]*i%D+D)%D])
			return putchar('0'+i),dfs(x-1,s-i,(r-pw[x-1]*i%D+D)%D,0);
}

int main()
{
	scanf("%d%d",&D,&S);pw[0]=1;
	int lim=max(S/9+5,500);
	f[0][0][0]=1;
	for(int i=1;i<=lim;i++)
		pw[i]=pw[i-1]*10%D;
	for(int i=1;i<=lim;i++)
	{
		for(int j=0;j<=S;j++)
			for(int k=0;k<=min(9,j);k++)
				f[i][j]|=f[i-1][j-k]<<(k*pw[i-1]%D)|f[i-1][j-k]>>(D-k*pw[i-1]%D);
		if(f[i][S][0]) return dfs(i,S,0,1),puts(""),0;
	}
	puts("-1");
}