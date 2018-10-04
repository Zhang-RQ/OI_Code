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
#include<bitset>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;

ll l1,r1,l2,r2,m;

void print_bit(ll v){cout<<bitset<20>(v)<<" ";}

ll solve(ll R1,ll R2)
{
	ll ret=0;
	for(int i=60;~i;--i)
		for(int j=60;~j;--j)
			if(((R1>>i)&1)&&((R2>>j)&1))
			{
				ll tms=(1ll<<min(i,j))%P;
				ll l=((R1-(1ll<<i))^(R2-(1ll<<j)))&(~((1ll<<max(i,j))-1));
				(ret+=((l+(1ll<<max(i,j))-1)/m-l/m+(l%m==0))%P*tms%P)%=P;
			}
	return ret;
}

int main()
{
	scanf("%lld%lld%lld%lld%lld",&l1,&r1,&l2,&r2,&m);
	ll Ans=solve(r1+1,r2+1)-solve(r1+1,l2)-solve(l1,r2+1)+solve(l1,l2);
	(Ans=Ans%P+P)%=P;
	printf("%lld\n",Ans);
}