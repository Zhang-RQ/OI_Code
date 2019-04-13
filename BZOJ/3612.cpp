#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=10010;

int n,k,P;
int f[12][MAXN*10];

void solve()
{
	memset(f,0,sizeof f);
	f[0][0]=1;
	scanf("%d%d%d",&n,&k,&P);
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n*k;j++)
		{
			f[i][j]=(f[i][j-i]+f[i-1][j-i])%P;
			if(j>=n+1) f[i][j]=(f[i][j]-f[i-1][j-n-1]+P)%P;
		}
	int Ans=0;
	for(int i=0;i<=k;i++)
		for(int j=0;j<=n*k;j++)
			Ans=(Ans+1ll*f[i][j]*f[k-i][j])%P;
	for(int i=0;i<=k-1;i++)
		for(int j=0;j<=n*k;j++)
			Ans=(Ans+1ll*f[i][j]*f[k-i-1][j])%P;
	printf("%d\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
