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

const int MAXN=1510;

int s[MAXN][MAXN],mx[MAXN][MAXN],m,k,n;
int lu[MAXN][MAXN],ld[MAXN][MAXN],ru[MAXN][MAXN],rd[MAXN][MAXN];
int Ans;

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,x;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&x),s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+x;
	for(int i=k;i<=n;i++)
		for(int j=k;j<=m;j++)
			mx[i][j]=s[i][j]-s[i-k][j]-s[i][j-k]+s[i-k][j-k];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			lu[i][j]=max(mx[i][j],max(lu[i-1][j],lu[i][j-1]));
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--)
			ru[i][j]=max(mx[i][j],max(ru[i-1][j],ru[i][j+1]));
	for(int i=n;i>=1;i--)
		for(int j=1;j<=m;j++)
			ld[i][j]=max(mx[i][j],max(ld[i+1][j],ld[i][j-1]));
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
			rd[i][j]=max(mx[i][j],max(rd[i+1][j],rd[i][j+1]));

	for(int i=k;i<=n-k;i++)
		for(int j=k;j<=m-k;j++)
			Ans=max(Ans,lu[i][j]+ru[i][j+k]+ld[i+k][m]);
	for(int i=k;i<=n-k;i++)
		for(int j=k;j<=m-k;j++)
			Ans=max(Ans,lu[i][m]+ld[i+k][j]+rd[i+k][j+k]);
	for(int i=k;i<=n-k;i++)
		for(int j=k;j<=m-k;j++)
			Ans=max(Ans,lu[i][j]+ru[n][j+k]+ld[i+k][j]);
	for(int i=k;i<=n-k;i++)
		for(int j=k;j<=m-k;j++)
			Ans=max(Ans,lu[n][j]+ru[i][j+k]+rd[i+k][j+k]);
	for(int i=k;i<=n-k;i++)
		for(int j=k+k;j<=m-k;j++)
			Ans=max(Ans,lu[n][j-k]+ru[n][j+k]+mx[i][j]);
	for(int i=k+k;i<=n-k;i++)
		for(int j=k;j<=m-k;j++)
			Ans=max(Ans,lu[i-k][m]+ld[i+k][m]+mx[i][j]);
	printf("%d\n",Ans);
}