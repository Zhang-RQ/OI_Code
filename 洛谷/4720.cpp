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

ll n,m,P;

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=(a/b)*x;
}

ll ksm(ll a,ll b,ll P)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll inv(ll n,ll p)
{
	ll x,y;
	exgcd(n,p,x,y);
	x=(x%p+p)%p;
	return x;
}

pair<ll,ll> CRT(ll k1,ll m1,ll k2,ll m2)
{
	ll x,y,Mod=m1*m2;exgcd(m1,m2,x,y);y=-y;
	x=(x*(k2-k1)%m2+m2)%m2;
	return make_pair((k1+x*m1%Mod)%Mod,Mod);
}

ll fac(ll n,ll pi,ll pk)
{
	if(!n) return 1;
	ll ret=1;
	for(int i=1;i<=pk;i++)
		if(i%pi) (ret*=i)%=pk;
	ret=ksm(ret,n/pk,pk);
	for(int i=1;i<=n%pk;i++)
		if(i%pi) (ret*=i)%=pk;
	return ret*fac(n/pi,pi,pk)%pk;
}

ll C(ll n,ll m,ll pi,ll pk)
{
	ll t1=fac(n,pi,pk),t2=fac(m,pi,pk),t3=fac(n-m,pi,pk);
	ll tms=0;
	for(ll x=n;x;x/=pi) tms+=x/pi;
	for(ll x=m;x;x/=pi) tms-=x/pi;
	for(ll x=n-m;x;x/=pi) tms-=x/pi;
	return t1*inv(t2,pk)%pk*inv(t3,pk)%pk*ksm(pi,tms,pk)%pk;
}

ll exLucas(ll n,ll m,ll P)
{
	ll t=P,Res=0,Mod=1;
	for(int i=2;1ll*i*i<=P;i++)
		if(!(t%i))
		{
			ll pk=1;
			while(!(t%i))
				t/=i,pk*=i;
			pair<ll,ll> tmp=CRT(C(n,m,i,pk),pk,Res,Mod);
			Res=tmp.first;Mod=tmp.second;
		}
	if(t!=1)
	{
		pair<ll,ll> tmp=CRT(C(n,m,t,t),t,Res,Mod);
		Res=tmp.first;Mod=tmp.second;
	}
	return Res;
}

int main()
{
	cin>>n>>m>>P;
	cout<<exLucas(n,m,P)<<endl;
}