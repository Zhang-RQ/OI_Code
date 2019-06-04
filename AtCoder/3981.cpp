#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1E5+10;
const int MAXK=16;
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

int n,m,a[MAXK+2],f[2][1<<MAXK];
ll fac[MAXN],ifac[MAXN];

ll C(int n,int m)
{
	if(n<0||m<0||n<m)
		return 0;
	return fac[n]*ifac[n-m]%P*ifac[m]%P;
}

int main()
{
	scanf("%d%d",&n,&m);
	int lim=1<<n;
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=lim;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[lim]=ksm(fac[lim],P-2);
	for(int i=lim-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	int lst=0;
	f[lst][0]=1;
	for(int i=m;i;i--)
	{
		memcpy(f[!lst],f[lst],sizeof f[!lst]);
		for(int s=0;s<1<<n;s++)
			if(f[lst][s])
				for(int j=0;j<n;j++)
					if(!((s>>j)&1))
						Inc(f[!lst][s|(1<<j)],f[lst][s]*C(lim-s-a[i],(1<<j)-1)%P*fac[1<<j]%P);
		lst^=1;
	}
	ll Ans=0;
	for(int s=0;s<1<<n;s++)
	{
		if(__builtin_popcount(s)&1)
			Dec(Ans,f[lst][s]*fac[lim-s-1]%P);
		else
			Inc(Ans,f[lst][s]*fac[lim-s-1]%P);
	}
	Ans=Ans*(1ll<<n)%P;
	printf("%lld\n",Ans);
}
