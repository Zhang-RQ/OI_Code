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
const int P=1E9+7;

int n,k,f[MAXN][MAXN][2][2],h[MAXN],g[MAXN],fac[MAXN],C[MAXN][MAXN];

inline void inc(int &x,int y){x+=y;if(x>P) x-=P;}
inline void dec(int &x,int y){x-=y;if(x<0) x+=P;}

int main()
{
	scanf("%d%d",&n,&k);fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%P;
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			inc(C[i][j],C[i-1][j-1]),inc(C[i][j],C[i-1][j]);
	}
	f[0][0][1][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
		{
			if(j) inc(f[i][j][0][1],f[i-1][j-1][0][0]),inc(f[i][j][0][1],f[i-1][j-1][1][0]);
			if(j) inc(f[i][j][1][1],f[i-1][j-1][0][1]),inc(f[i][j][1][1],f[i-1][j-1][1][1]);
			inc(f[i][j][0][0],j?f[i-1][j-1][0][0]:0);inc(f[i][j][0][0],f[i-1][j][0][0]);inc(f[i][j][0][0],f[i-1][j][1][0]);
			inc(f[i][j][1][0],j?f[i-1][j-1][0][1]:0);inc(f[i][j][1][0],f[i-1][j][0][1]);inc(f[i][j][1][0],f[i-1][j][1][1]);
		}
	for(int i=0;i<=n;i++)
		inc(h[i],1ll*f[n][i][0][0]*fac[n-i]%P),inc(h[i],1ll*f[n][i][1][0]*fac[n-i]%P);
	for(int i=n;i;i--)
		for(int j=i-1;~j;j--)
			dec(h[j],1ll*h[i]*C[i][j]%P);
	printf("%d\n",h[k]);
}