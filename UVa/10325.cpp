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

ll n,m,a[20],Ans;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

ll lcm(ll a,ll b){return 1ll*a/gcd(a,b)*b;}

bool solve()
{
	Ans=0;
	if(scanf("%lld%lld",&n,&m)==EOF) return false;
	for(int i=1;i<=m;i++) scanf("%lld",&a[i]);
	ll LCM=0;
	for(int s=0;s<1<<m;s++)
	{
		LCM=1;
		for(int i=0;i<m;i++)
			if((s>>i)&1) LCM=lcm(a[i+1],LCM);
		Ans+=(__builtin_popcount(s)&1?-1:1)*(n/LCM);
	}
	return printf("%lld\n",Ans),1;
}

int main()
{
	while(solve());
}