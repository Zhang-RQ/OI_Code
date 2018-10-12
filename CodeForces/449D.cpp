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

const int MAXS=1<<20;
const int P=1E9+7;

int f[MAXS],pw[MAXS],n,mx;
ll Ans;

int main()
{
	scanf("%d",&n);
	pw[0]=1;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		f[x]++;mx=max(mx,x);
	}
	for(int i=1;i<1<<20;i++) pw[i]=2*pw[i-1]%P;
	for(int i=0;i<20;i++)
		for(int s=(1<<20)-1;~s;s--)
			if(!((s>>i)&1))
				(f[s]+=f[s^(1<<i)])%=P;
	for(int s=0;s<1<<20;s++)
		Ans=(Ans+(__builtin_popcount(s)&1?-1:1)*(pw[f[s]]-1)%P+P)%P;
	printf("%lld\n",Ans);
}