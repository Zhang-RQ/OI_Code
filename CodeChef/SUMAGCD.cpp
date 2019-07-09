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

ll S1(ll n)
{
	n%=P;
	return n*(n+1)/2%P;
}

int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

void solve()
{
	int n,k,x;
	vector<int> a,pre,suf;
	scanf("%d",&n);
	a.resize(n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
	if(a.size()==1)
		return printf("%d\n",a[0]<<1),void();
	int Ans=0;
	pre.resize(a.size());suf.resize(a.size());
	pre[0]=a[0];suf.back()=a.back();
	for(int i=1;i<a.size();i++)
		pre[i]=gcd(pre[i-1],a[i]);
	for(int i=(int)a.size()-2;~i;i--)
		suf[i]=gcd(suf[i+1],a[i]);
	for(int i=0;i<a.size();i++)
		Ans=max(Ans,a[i]+gcd(i?pre[i-1]:0,i+1==a.size()?0:suf[i+1]));
	printf("%d\n",Ans);
}

int main()
{
	int T;
	for(scanf("%d",&T);T--;solve());
}
