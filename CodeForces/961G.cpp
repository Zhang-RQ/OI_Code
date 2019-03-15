#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=2E5+10;
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
	if(b<0) b+=P-1;
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int n,k;
ll fac[MAXN],ifac[MAXN],s;

int main()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<=2E5;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[200000]=ksm(fac[200000],P-2);
	for(int i=199999;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	scanf("%d%d",&n,&k);
	ll Ans=0;
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),Inc(s,x);
	for(int i=0;i<=k-1;i++)
		if((k-1-i)&1)
			Dec(Ans,1ll*(n+i)*ksm(i+1,n-2)%P*ifac[i]%P*ifac[k-1-i]%P);
		else
			Inc(Ans,1ll*(n+i)*ksm(i+1,n-2)%P*ifac[i]%P*ifac[k-1-i]%P);
	printf("%lld\n",Ans*s%P);
}
