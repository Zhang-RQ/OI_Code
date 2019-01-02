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
const int MAXM=10010;
const int P=998244353;

int p[MAXN],n,m,k;
int f[2][15][MAXM];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int main()
{
	scanf("%d%d%d",&n,&k,&m);k=n-k+1;
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=k;i++) f[0][i][0]=P-1;
	for(int i=1;i<=n;i++)
	{
		int nw=i&1;
		for(int j=0;j<=k;j++)
			for(int l=0;l<=m;l++)
			{
				f[nw][j][l]=f[!nw][j][l];
				if(l>=p[i])
					(f[nw][j][l]+=(-f[!nw][j][l-p[i]]+(j?f[!nw][j-1][l-p[i]]:0)+P)%P)%=P;
			}
	}
	int Ans=0;
	for(int i=1;i<=m;i++)
		Ans=(Ans+1ll*m*ksm(i,P-2)%P*f[n&1][k][i]%P)%P;
	printf("%d\n",Ans);
}