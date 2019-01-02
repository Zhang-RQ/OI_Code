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

const int P=998244353;

ll solve(ll x)
{
	ll ret=0;
	for(ll d=1,p=0;d<=x;d=p+1)
	{
		p=x/(x/d);
		(ret+=(x/d)*(p-d+1)%P)%=P;
	}
	return ret;
}

int main()
{
	ll l,r;
	cin>>l>>r;
	cout<<(solve(r)-solve(l-1)+P)%P<<endl;
}