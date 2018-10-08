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

inline ll mul(ll a,ll b,ll P)
{
	if(a<2E9&&b<2E9) return a*b%P;
	ll ret=0;
	for(;b;b>>=1,(a+=a)%=P) if(b&1) (ret+=a)%=P;
	return ret;
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y) // ax+by=gcd(a,b)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,x,y);
	ll t=x;x=y;y=t-(a/b)*y;
}


pair<ll,ll> exCRT(pair<ll,ll> l,pair<ll,ll> r) //x=l.first (l.second)
{
	if(r.first<l.first) swap(l,r);
	ll tx,ty;
	ll d=gcd(l.second,r.second),tms=(r.first-l.first)/d;
	ll LCM=l.second/d*r.second;
	exgcd(l.second,r.second,tx,ty);
	tx=(tx%LCM+LCM)%LCM;tx=mul(tx,tms,LCM);
	return make_pair((l.first+mul(l.second,tx,LCM)+LCM)%LCM,LCM);
}

int main()
{
	int n;pair<ll,ll> Res;
	scanf("%d",&n);
	scanf("%lld%lld",&Res.second,&Res.first);
	for(int i=2;i<=n;i++)
	{
		pair<ll,ll> tmp;
		scanf("%lld%lld",&tmp.second,&tmp.first);
		Res=exCRT(Res,tmp);
	}
	printf("%lld\n",Res.first%Res.second);
}