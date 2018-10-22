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

const int MAXN=1010;
const int P=10000;

int n,k,f[MAXN][MAXN],s[MAXN][MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	if(n*(n-1)/2<k) return puts("0"),0;
	s[1][0]=f[1][0]=1;
	for(int i=1;i<=k;i++)
		s[1][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=0;j<=k;j++)
		{
			f[i][j]=(s[i-1][j]-(j-i<0?0:s[i-1][j-i])+P)%P;
			if(j) (s[i][j]=s[i][j-1]+f[i][j])%=P;
			else s[i][j]=1;
		}
	printf("%d\n",f[n][k]);
}