#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=3010;
const int MAXM=310;

int n,m,now[MAXM];
double f[MAXM][MAXN],dlt[MAXN],p[MAXN][MAXM];

void update(int x)
{
	double lstf=f[x][0],nf=0;
	f[x][0]=0;
	for(int i=1;i<=n;i++)
	{
		nf=f[x][i];
		f[x][i]=f[x][i-1]*(1-p[i][x])+lstf*p[i][x];
		lstf=nf;
	}
	dlt[x]-=f[x][n];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&p[i][j]),
			p[i][j]/=1000;
	for(int i=1;i<=m;i++)
	{
		dlt[i]=1;f[i][0]=1;
		for(int j=1;j<=n;j++)
			f[i][j]=f[i][j-1]*(1-p[j][i]);
		dlt[i]-=f[i][n];
	}
	double Ans=0;
	int t=n;
	while(t--)
	{
		int mx=0;
		for(int i=1;i<=m;i++)
			if(dlt[i]>dlt[mx])
				mx=i;
		Ans+=dlt[mx];update(mx);
	}
	printf("%.12lf\n",Ans);
}
