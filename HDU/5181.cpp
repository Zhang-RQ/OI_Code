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

const int P=1E9+7;
const int MAXN=410;

int n,m,sum[MAXN][MAXN];
ll f[MAXN][MAXN];

inline int ask(int l1,int r1,int l2,int r2)
{
	if(l1>r1||l2>r2) return 0;
	return sum[r1][r2]-sum[r1][l2-1]-sum[l1-1][r2]+sum[l1-1][l2-1];
}

inline void inc(ll &x,ll y){x+=y;if(x>=P) x-=P;}

void solve()
{
	memset(sum,0,sizeof sum);
	memset(f,0,sizeof f);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),sum[u][v]++;
	for(int i=1;i<=n;i++)
		if(sum[i][i]) return puts("0"),void();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
	for(int i=1;i<=n;i++) f[i][i]=1;
	for(int len=2;len<=n;len++)
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			f[l][l-1]=f[r+1][r]=1;
			for(int k=l;k<=r;k++)
				if(ask(k+1,r,l,k-1)+ask(k,k,l,r)==0)
					inc(f[l][r],f[l][k-1]*f[k+1][r]%P);//,printf("%d -> %d,%d\n",k,l,r);
		}
	printf("%lld\n",f[1][n]);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
