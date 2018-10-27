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

map<ll,int> mp;

int n,tot;
ll fib[233];

int solve(ll x)
{
	if(!x) return 0;
	if(mp.find(x)!=mp.end()) return mp[x];
	int p=lower_bound(fib+1,fib+1+tot,x)-fib;
	int ret=mp[x]=min(solve(fib[p]-x),solve(x-fib[p-1]))+1;
	return ret;
}

int main()
{
	fib[1]=fib[2]=1;mp[1]=1;
	for(int i=3;i<=200;i++)
	{
		fib[i]=fib[i-1]+fib[i-2];
		tot=i;mp[fib[i]]=1;
		if(fib[i]>5E17) break;
	}
	int T;ll x;
	scanf("%d",&T);
	while(T--) scanf("%lld",&x),printf("%d\n",solve(x));
}