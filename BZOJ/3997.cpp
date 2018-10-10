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

const int MAXN=1E3+10;

int a[MAXN][MAXN],n,m;
ll f[MAXN][MAXN],Ans;

void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--)
			f[i][j]=max(f[i-1][j+1]+a[i][j],max(f[i-1][j],f[i][j+1]));
	printf("%lld\n",f[n][1]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}