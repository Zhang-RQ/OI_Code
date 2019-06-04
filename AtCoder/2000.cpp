#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=4E6+10;
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

int n,k;
ll fac[MAXN],ifac[MAXN],f[2010][2010];

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
	scanf("%d%d",&n,&k);
	if(k==1)
		return puts("1"),0;
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=i;~j;j--)
			f[i][j]=Add(f[i][j+1],j?(C(i*k-j-1,k-2)*f[i-1][j-1]%P):0);
	printf("%lld\n",f[n][0]*fac[n]%P);
}
