#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1010;

int n;
ll bs[64];
pair<ll,ll> p[MAXN];

bool insert(ll v)
{
	for(int i=62;~i;i--)
		if((v>>i)&1)
		{
			if(bs[i]) v^=bs[i];
			else return bs[i]=v,1;
		}
	return 0;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i].second,&p[i].first);
	sort(p+1,p+1+n,greater<pair<ll,ll> >());
	ll Ans=0;
	for(int i=1;i<=n;i++)
		Ans+=insert(p[i].second)*p[i].first;
	printf("%lld\n",Ans);
}
