#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=25;
const double EPS=1E-9;

int n,m,k,x,y,tp[MAXN];
double f[MAXN][MAXN],P[MAXN][MAXN],C[MAXN][MAXN];

double dp(int t)
{
	memset(f,0,sizeof f);
	f[1][1]=C[1][tp[1]];
	for(int i=1;i<k;i++)
		for(int j=1;j<=n;j++)
		{
			if(t&&i==x&&j!=y)
				f[i][j]=0;
			for(int z=1;z<=n;z++)
				f[i+1][z]+=f[i][j]*P[j][z]*C[z][tp[i+1]];
		}
	double ret=0;
	for(int i=1;i<=n;i++)
	{
		if(t&&x==k&&i!=y)
			continue;
		ret+=f[k][i];
	}
	return ret;
}

void solve()
{
	scanf("%d%d%d%d%d",&n,&m,&k,&x,&y);++x;++y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&P[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&C[i][j]);
	for(int i=1;i<=k;i++)
		scanf("%d",&tp[i]),++tp[i];
	printf("%.3lf\n",dp(1)/dp(0));
}

int main()
{
	freopen("trip.in","r",stdin);
	int T;
	for(scanf("%d",&T);T--;solve());
}
