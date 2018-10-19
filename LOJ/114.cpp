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

int cnt,n;
ll bs[64],S;

void insert(ll x)
{
	for(int i=62;~i;i--)
		if((x>>i)&1)
		{
			if(!bs[i]) {bs[i]=x;break;}
			else x^=bs[i];
		}
}

ll Query(ll k)
{
	if(cnt!=n) --k;
	if(k>=S) return -1;
	ll ret=0;int t=cnt-1;
	for(int i=62;~i;i--)
	{
		if(!bs[i]) continue;
		if((k>>t)&1) ret^=bs[i];
		t--;
	}
	return ret;
}

int main()
{
	int m;ll x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x),insert(x);
	for(int i=62;~i;i--)
		for(int j=i-1;~j;j--)
			if(((bs[i]>>j)&1))
				bs[i]^=bs[j];
	for(int i=62;~i;i--)
		if(bs[i])
			++cnt;
	S=1ll<<cnt;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&x);
		printf("%lld\n",Query(x));
	}
}