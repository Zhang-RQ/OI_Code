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

const int MAXN=55;
const int MAXS=1<<15;
const int P=1E9;

int n,m,c[MAXN];
int f[MAXN][MAXS];

void solve()
{
	scanf("%d%d",&n,&m);memset(f,0,sizeof f);
	int ful=(1<<m)-1;
	for(int s=0;s<1<<m;s++)
		f[0][s]=1;
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<1<<m;j++)
			if(j%c[i])
				(f[i][j]+=f[i-1][j^ful])%=P;
		for(int j=0;j<m;j++)
			for(int s=0;s<1<<m;s++)
				if((s>>j)&1)
					(f[i][s]+=f[i][s^(1<<j)])%=P;
	}
	printf("%d\n",f[n][ful]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}