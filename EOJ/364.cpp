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

const int P=1E9+7;

ll n,m,pw[15],PW[15];

pair<ll,ll> operator + (const pair<ll,ll> &lhs,const pair<ll,ll> &rhs) {return make_pair((lhs.first+rhs.first)%P,(lhs.second+rhs.second)%P);}

namespace solve1{ // m<=99
	int N[15],M[15],totn,totm,nxt[15]; //begin with 1
	bool vis[15][100][100][15][2];
	pair<ll,ll> f[15][100][100][15][2];
	ll m,n;	
	
	pair<ll,ll> dfs(int x,int s1,int s2,int len,bool lim,bool ok)
	{
		if(x>totn) return (ok||s1==0||s2==0)?make_pair(1ll,0ll):make_pair(0ll,0ll);
		if(vis[x][s1][s2][len][ok]&&!lim) return f[x][s1][s2][len][ok];
		pair<ll,ll> ret=make_pair(0,0);
		int lm=lim?N[x]:9;
		for(int i=0;i<=lm;i++)
		{
			int t=len,Mat=0;
			while(t&&M[t+1]!=i) t=nxt[t];
			if(M[t+1]==i) ++t;
			if(t==totm) t=nxt[t],Mat=1;
			pair<ll,ll> tp=dfs(x+1,(s1*10+i)%m,(s2+i)%m,t,lim&&i==lm,ok||Mat);
			(ret.second+=i*pw[totn-x]*tp.first%P)%=P;
			ret=ret+tp;
		}
		if(!lim) vis[x][s1][s2][len][ok]=1,f[x][s1][s2][len][ok]=ret;
		return ret;
	}

	void solve(ll nn,ll mm)
	{
		n=nn;m=mm;
		while(nn) N[++totn]=nn%10,nn/=10;
		while(mm) M[++totm]=mm%10,mm/=10;
		reverse(N+1,N+1+totn);reverse(M+1,M+1+totm);
		for(int i=2,j=0;i<=totm;i++)
		{
			while(j&&M[j+1]!=M[i]) j=nxt[j];
			if(M[j+1]==M[i]) nxt[i]=++j;
			else nxt[i]=0;
		}
		pair<ll,ll> Res=dfs(1,0,0,0,1,0);
		Res.first--;n%=P;
		if(Res.first<0) Res.first+=P;
		printf("%lld\n",((n+1)*Res.first%P-Res.second%P+n+P)%P);
	}
}

namespace solve2{ // m<=100000
	int N[15],M[15],totn,totm,nxt[15]; //begin with 1
	bool vis[13][100000][13][2];
	pair<ll,ll> f[13][100000][13][2];
	ll m,n;	
	
	pair<ll,ll> dfs(int x,int s1,int len,bool lim,bool ok)
	{
		if(x>totn) return (ok||s1==0)?make_pair(1ll,0ll):make_pair(0ll,0ll);
		if(vis[x][s1][len][ok]&&!lim) return f[x][s1][len][ok];
		pair<ll,ll> ret=make_pair(0,0);
		int lm=lim?N[x]:9;
		for(int i=0;i<=lm;i++)
		{
			int t=len,Mat=0;
			while(t&&M[t+1]!=i) t=nxt[t];
			if(M[t+1]==i) ++t;
			if(t==totm) t=nxt[t],Mat=1;
			pair<ll,ll> tp=dfs(x+1,(s1*10+i)%m,t,lim&&i==lm,ok||Mat);
			(ret.second+=i*pw[totn-x]*tp.first%P)%=P;
			ret=ret+tp;
		}
		if(!lim) vis[x][s1][len][ok]=1,f[x][s1][len][ok]=ret;
		return ret;
	}

	void solve(ll nn,ll mm)
	{
		n=nn;m=mm;
		while(nn) N[++totn]=nn%10,nn/=10;
		while(mm) M[++totm]=mm%10,mm/=10;
		reverse(N+1,N+1+totn);reverse(M+1,M+1+totm);
		for(int i=2,j=0;i<=totm;i++)
		{
			while(j&&M[j+1]!=M[i]) j=nxt[j];
			if(M[j+1]==M[i]) nxt[i]=++j;
			else nxt[i]=0;
		}
		pair<ll,ll> Res=dfs(1,0,0,1,0);
		Res.first--;n%=P;
		if(Res.first<0) Res.first+=P;
		printf("%lld\n",((n+1)*Res.first%P-Res.second%P+n+P)%P);
	}
}

namespace solve3{
	int totn,totm;
	set<ll> s;
	ll n,m;

	void dfs(int x,ll cur,bool f)
	{
		if(cur>n||(!f&&x+totm-1>totn)) return;
		if(x>totn)
		{
			if(f) s.insert(cur);
			return;
		}
		for(int i=0;i<=9;i++)
			dfs(x+1,cur+PW[totn-x]*i,f);
		if(x+totm-1<=totn&&!f)
			dfs(x+totm,cur+m*PW[totn-x+1-totm],1);
	}

	void solve(ll _n,ll _m)
	{
		n=_n;m=_m;
		while(_n) _n/=10,++totn;
		while(_m) _m/=10,++totm;
		for(ll i=m;i<=n;i+=m)
			s.insert(i);
		dfs(1,0,0);
		s.erase(0);
		ll Ans1=s.size(),Ans2=0;
		for(ll v:s)
			(Ans2+=v)%=P;
		printf("%lld\n",((n+1)*Ans1%P-Ans2%P+n+P)%P);
	}
}

int main()
{
	pw[0]=PW[0]=1;
	for(int i=1;i<=12;i++) pw[i]=pw[i-1]*10%P,PW[i]=PW[i-1]*10;
	scanf("%lld%lld",&n,&m);
	if(m<=99) solve1::solve(n,m);
	else if(m<=100000) solve2::solve(n,m);
	else solve3::solve(n,m);
}