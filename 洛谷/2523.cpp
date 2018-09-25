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

const int MAXN=310;

int n,m,P;
int f[MAXN][MAXN],c[MAXN][MAXN],s[MAXN];

void solve()
{
	scanf("%d%d%d",&n,&m,&P);
	memset(s,0,sizeof s);memset(f,0,sizeof f);
	for(int i=1,p,q;i<=m;i++)
	{
		scanf("%d%d",&p,&q);
		s[q]++;
	}
	for(int i=n;i;i--) s[i]+=s[i+1];
	for(int i=1;i<=n;i++) if(s[i]>n-i+1) return puts("NO"),void();
	for(int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%P;
	}
	f[n+1][0]=1;
	for(int i=n;i;i--)
		for(int j=0;j<=n-s[i]-i+1;j++)
			for(int k=0;k<=j;k++)
				f[i][j]=(f[i][j]+1ll*f[i+1][j-k]*c[j][k]%P)%P;
	printf("YES %d\n",f[1][n-m]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}