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

const int MAXN=1E5+10;

int n,m,P;
ll fac[MAXN],ifac[MAXN];

inline ll C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

ll Lucas(int n,int m)
{
	if(n<m) return 0;
	if(n<P&&m<P) return C(n,m);
	return C(n%P,m%P)*Lucas(n/P,m/P)%P;
}

void solve()
{
	scanf("%d%d%d",&n,&m,&P);
	fac[0]=ifac[0]=1;
	for(int i=1;i<P;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[P-1]=P-1;
	for(int i=P-2;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	printf("%lld\n",Lucas(n+m,m));
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}