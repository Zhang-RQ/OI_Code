#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E5+10;
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
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P)
		if(b&1)
			(ret*=a)%=P;
	return ret;
}

int n,m;
ll fac[MAXN],ifac[MAXN];

ll C(ll n,ll m)
{
	if(n<0||m<0||n<m)
		return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

int main()
{
	scanf("%d%d",&n,&m);
	if(n<m)
		return puts("0"),0;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=2*n;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[2*n]=ksm(fac[2*n],P-2);
	for(int i=2*n-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	ll up=0,down=0;
	ll Ans=C(2*n,n);
	for(int i=1;i<=n;i++)
	{
		up=2*(m+1)-up;down=-2-down;
		if(i&1)
			Dec(Ans,Add(C(2*n,(2*n+up)/2),C(2*n,(2*n+down)/2)));
		else
			Inc(Ans,Add(C(2*n,(2*n+up)/2),C(2*n,(2*n+down)/2)));
		swap(up,down);
	}
	printf("%lld\n",Ans);
}
