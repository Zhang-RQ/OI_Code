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

int n,k;
bool f[MAXN][MAXN];
ll a[MAXN],cur,sum[MAXN];

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	for(int b=60;~b;--b)
	{
		memset(f,0,sizeof f);
		f[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=k;j++)
				for(int l=1;l<=i;l++)
					f[i][j]|=f[l-1][j-1]&&(((sum[i]-sum[l-1])&cur)==cur)&&(((sum[i]-sum[l-1])>>b)&1);//[l,i]
		if(f[n][k]) cur|=1ll<<b;
	}
	printf("%lld\n",cur);
}