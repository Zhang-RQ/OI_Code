#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXK=60;
const int MAXT=1E4+10;
const int LIM=1E5+10;

namespace Pollard_Rho{
	const int pr[]={2,3,5,7,11,23,43,79};
	const int M=(1<<8)-1;

	mt19937 RandEngine(chrono::steady_clock::now().time_since_epoch().count());
	ll RandInt(ll L,ll R){return uniform_int_distribution<ll>(L,R)(RandEngine);}
	vector<ll> Res;

	ll Mx=0;

	ll gcd(ll a,ll b)
	{
		if(!a||!b) return a|b;
#define ctz __builtin_ctzll
		int shift=ctz(a|b);
		b>>=ctz(b);
		while(a)
		{
			a>>=ctz(a);
			if(a<b)
				swap(a,b);
			a-=b;
		}
		return b<<shift;
#undef ctz
	}

	ull Mul(ull a,ull b,ull P)
	{
		ull c=(ll)a*b-(ll)((ull)((long double)a*b/P))*P;
		return (c+P)%P;
	}

	ll ksm(ll a,ll b,ll P)
	{
		ll ret=1;
		for(;b;b>>=1,a=Mul(a,a,P))
			if(b&1)
				ret=Mul(ret,a,P);
		return ret;
	}

	bool Miller_Rabin(ll n)
	{
		if(n==2||n==3||n==5||n==7||n==11||n==23||n==43||n==79)
			return true;
		if(~n&1)
			return false;
		for(int p:pr)
		{
			ll t=n-1,c=0;
			while(~t&1)
				t>>=1,++c;
			ll pw=ksm(p,t,n);
			if(pw==1)
				continue;
			bool f=(pw==n-1);
			while(c)
			{
				pw=Mul(pw,pw,n);
				f|=(pw==n-1);
				--c;
				if(pw==1&&!f)
					return false;
			}
			if(pw!=1||!f)
				return false;
		}
		return true;
	}

	ll Pollard_Rho(ll n)
	{
		int c=RandInt(1,n-1);
		ll t=1,x=0,y=0,q=1;
		auto F=[=](ll x){return (Mul(x,x,n)+c)%n;};
		for(int i=2;;i<<=1,y=x,q=1)
		{
			for(int j=1;j<=i;j++)
			{
				x=F(x);
				q=Mul(q,abs(x-y),n);
				if(!(j&M))
				{
					if((t=gcd(q,n))>1)
						break;
				}
			}
			if(t>1||((t=gcd(q,n))>1))
				break;
		}
		if(t==n)
		{
			t=1;
			while(t==1)
				x=F(x),t=gcd(abs(x-y),n);
		}
		return t;
	}

	void Factorize(ll n)
	{
		if(Miller_Rabin(n))
			return Res.push_back(n),void();
		ll d=n;
		while(d==n)
			d=Pollard_Rho(n);
		Factorize(n/d);Factorize(d);
	}

	vector<ll> solve(ll n)
	{
		Res.clear();
		Factorize(n);
		return Res;
	}
}

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=(a/b)*x;
}

int Ans[MAXT],tot;
ll dis[LIM];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > pq;
vector<ll> pr;
map<ll,int> M;
vector<pair<ll,int> > Q[MAXK];

void Dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[0]=0;pq.emplace(0,0);
	while(!pq.empty())
	{
		auto x=pq.top();pq.pop();
		if(x.first!=dis[x.second])
			continue;
		for(ll p:pr)
		{
			ll v=(p+x.second)%pr[0];
			if(dis[v]<=x.first+p)
				continue;
			dis[v]=x.first+p;
			pq.emplace(dis[v],v);
		}
	}
}

int main()
{
	int T,tst=0;
	scanf("%d",&T);
	for(ll n,k;T;T--)
	{
		scanf("%lld%lld",&n,&k);
		if(!M.count(k))
			M[k]=++tot;
		int id=M[k];
		Q[id].emplace_back(n,++tst);
	}
	for(auto pK:M)
	{
		int idx=pK.second;
		ll K=pK.first;
		if(K==1)
			continue;
		pr=Pollard_Rho::solve(K);
		if(pr.size()==1)
		{
			for(auto q:Q[idx])
				Ans[q.second]=q.first%K==0;
		}
		else if(pr.size()==2)
		{
			for(auto q:Q[idx])
			{
				ll x,y;
				exgcd(pr[0],pr[1],x,y);
				x=(x%pr[1]+pr[1])%pr[1];
				ll fx=Pollard_Rho::Mul(x,q.first,pr[1]),fy;
				fy=(q.first-fx*pr[0])/pr[1];
				Ans[q.second]=fx>=0&&fy>=0;
			}
		}
		else
		{
			sort(pr.begin(),pr.end());
			Dijkstra();
			for(auto q:Q[idx])
				Ans[q.second]=dis[q.first%pr[0]]<=q.first;
		}
	}
	for(int i=1;i<=tst;i++)
		puts(Ans[i]?"YES":"NO");
}
