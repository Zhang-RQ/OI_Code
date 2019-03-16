#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;

template<typename T1,typename T2>
    void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
    void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
    T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
    T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

ll ksm(ll a,ll b)
{
    ll ret=1;a%=P;
    for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
    return ret;
}

namespace Quadratic_residue{
	mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
	inline int RandInt(int l,int r) {return uniform_int_distribution<int>(l,r)(RandEngine);}
	
	pair<ll,ll> Mul(pair<ll,ll> a,pair<ll,ll> b,ll f) //sec^2=f
	{
		return make_pair(Add(a.first*b.first%P,a.second*b.second%P*f%P),Add(a.first*b.second%P,a.second*b.first%P));
	}

	ll solve(ll n)
	{
		if(n<=1) return n;
		if(ksm(n,(P-1)/2)!=1) throw "N isn't quadratic residue";
		ll a=RandInt(1,n-1);
		while(ksm(Sub(a*a%P,n),(P-1)/2)!=P-1)
			a=RandInt(1,n-1);
		ll f=Sub(a*a%P,n);
		pair<ll,ll> Res=make_pair(1,0),t=make_pair(a,1);
		for(ll b=(P+1)/2;b;b>>=1,t=Mul(t,t,f))
			if(b&1) Res=Mul(Res,t,f);
		return min(Res.first,P-Res.first);
	}
}

int main()
{
	
}
