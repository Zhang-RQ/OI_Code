#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;

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
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

void solve()
{
	int n,k,x;
	vector<ll> a,b;
	scanf("%d",&n);
	a.resize(n);b.resize(n);
	for(int i=0;i<n;i++)
		scanf("%lld",&a[i]);
	scanf("%d%d",&k,&x);
	for(int i=0;i<n;i++)
		b[i]=(a[i]^x)-a[i];
	if(k==n)
	{
		ll sum=0,Ans=0;
		for(int i=0;i<n;i++)
			sum+=b[i],Ans+=a[i];
		printf("%lld\n",Ans+max(sum,0ll));
		return;
	}
	if(k&1)
	{
		ll Ans=0;
		for(int i=0;i<n;i++)
			Ans+=a[i];
		for(int i=0;i<n;i++)
			if(b[i]>0)
				Ans+=b[i];
		printf("%lld\n",Ans);
	}
	else
	{
		int cnt=0;
		ll Ans=0,tmp=0;
		for(int i=0;i<n;i++)
			Ans+=a[i];
		for(int i=0;i<n;i++)
			if(b[i]>0)
				tmp+=b[i],cnt++;
		if(~cnt&1)
			printf("%lld\n",Ans+tmp);
		else
		{
			ll mx=-(1ll<<60),mn=1ll<<60;
			for(int i=0;i<n;i++)
				if(b[i]>0)
					mn=min(mn,b[i]);
				else
					mx=max(mx,b[i]);
			printf("%lld\n",max(Ans+tmp+mx,Ans+tmp-mn));
		}
	}
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
