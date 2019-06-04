#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
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

int a,b;
ll fac[MAXN],ifac[MAXN];

ll C(int n,int m)
{
	if(n<0||m<0||n<m)
		return 0;
	return fac[n]*ifac[n-m]%P*ifac[m]%P;
}

int main()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<MAXN;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[MAXN-1]=ksm(fac[MAXN-1],P-2);
	for(int i=MAXN-2;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	scanf("%d%d",&a,&b);
	ll Ans=a+1;
	for(int i=max(1,b-a);i<b;i++)
		for(int j=max(1,2*(b-i)-a);j<=b-i;j++)
			Inc(Ans,C(b-1,i-1)*C(b-i-1,j-1)%P*C(a-2*(b-i)+j+2,2)%P);
	printf("%lld\n",Ans);
}
