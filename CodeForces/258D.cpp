#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;

int n,m,a[MAXN];
double f[MAXN][MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=a[i]>a[j];
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		for(int j=1;j<=n;j++)
		{
			if(j==a||j==b)
				continue;
			f[a][j]=f[b][j]=.5*(f[a][j]+f[b][j]);
			f[j][a]=f[j][b]=.5*(f[j][a]+f[j][b]);
		}
		f[a][b]=f[b][a]=.5*(f[a][b]+f[b][a]);
	}
	double Ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			Ans+=f[i][j];
	printf("%.10lf\n",Ans);
}
