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

const int MAXN=1E7+10;

bool vis[MAXN];
int pri[MAXN],tot,phi[MAXN];

void sieve()
{
	for(int i=2;i<MAXN;i++)
	{
		if(!vis[i]) pri[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*pri[j]<MAXN;j++)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]) phi[i*pri[j]]=phi[i]*(pri[j]-1);
			else phi[i*pri[j]]=phi[i]*pri[j];
		}
	}
}

ll ksm(ll a,ll b,int P)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll solve(int P)
{
	if(P==1) return 0;
	return ksm(2,solve(phi[P])+phi[P],P);
}

int main()
{
	int T,P;sieve();
	for(scanf("%d",&T);T--;scanf("%d",&P),printf("%lld\n",solve(P)));
}