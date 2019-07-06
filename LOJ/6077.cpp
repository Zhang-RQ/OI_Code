#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1E9+7;
const int MAXN=1E5+10;
const int MAXM=500;

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

int f[MAXM][MAXN],n,k,lim;
ll fac[MAXN*5],ifac[MAXN*5];

ll C(int n,int m)
{
	if(n<m||n<0||m<0)
		return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

int main()
{
	scanf("%d%d",&n,&k);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n+k;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[n+k]=ksm(fac[n+k],P-2);
	for(int i=n+k-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	lim=sqrt(2*k)+3;
	f[0][0]=1;
	ll Ans=C(k+n-1,n-1);
	for(int i=1;i<=lim;i++)
		for(int j=0;j<=k;j++)
		{
			f[i][j]=Add(j>=i?f[i][j-i]:0,j>=i?f[i-1][j-i]:0);
			if(j>=n+1)
				Dec(f[i][j],f[i-1][j-n-1]);
			if(i&1)
				Dec(Ans,f[i][j]*C(k-j+n-1,n-1)%P);
			else
				Inc(Ans,f[i][j]*C(k-j+n-1,n-1)%P);
		}
	printf("%lld\n",Ans);
}
