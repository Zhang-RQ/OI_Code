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

const int MAXN=510;
const int P=1E6+7;

int C[MAXN][MAXN],Ts;

void init()
{
	for(int i=0;i<=500;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
	}
}

void solve()
{
	int n,m,k,Ans=0;
	scanf("%d%d%d",&n,&m,&k);
	Ans=C[n*m][k];
	Ans=(Ans-(2*C[(n-1)*m][k]+2*C[n*(m-1)][k])%P+P)%P;
	Ans=(Ans+C[(n-2)*m][k]+C[n*(m-2)][k]+4*C[(n-1)*(m-1)][k])%P;
	Ans=(Ans-(2*C[(n-2)*(m-1)][k]+2*C[(n-1)*(m-2)][k])%P+P)%P;
	Ans=(Ans+C[(n-2)*(m-2)][k])%P;
	printf("Case %d: %d\n",++Ts,Ans);
}

int main()
{
	init();int T;
	for(scanf("%d",&T);T--;solve());
}