#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=25;
const int P=998244353;

template<typename T1,typename T2>
	void Inc(T1 &a,T2 b){a+=b;if(a>=P) a-=P;}

template<typename T1,typename T2>
	void Dec(T1 &a,T2 b){a-=b;if(a<0) a+=P;}

template<typename T1,typename T2>
	T1 Add(T1 a,T2 b){a+=b;return a>=P?a-P:a;}

template<typename T1,typename T2>
	T1 Sub(T1 a,T2 b){a-=b;return a<0?a+P:a;}

int n,a[MAXN],f[1<<20],g[1<<20];
ll sum[1<<20],fac[MAXN];

int main()
{
	scanf("%d",&n);
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%P;
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]),sum[1<<i]=a[i];
	for(int i=0;i<n;i++)
		for(int s=0;s<1<<n;s++)
			if((s>>i)&1)
				sum[s]+=sum[s^(1<<i)];
	f[0]=1;g[0]=1;
	for(int s=1;s<1<<n;s++)
	{
		if(sum[s]>=0)
			continue;
		for(int i=0;i<n;i++)
			if((s>>i)&1)
				Inc(f[s],f[s^(1<<i)]);
	}
	for(int s=1;s<1<<n;s++)
		for(int i=0;i<n;i++)
			if(((s>>i)&1)&&sum[s^(1<<i)]>=0)
				Inc(g[s],g[s^(1<<i)]);
	ll Ans=0;
	int ful=(1<<n)-1;
	for(int s=1;s<1<<n;s++)
		Inc(Ans,1ll*(P+sum[s]%P)%P*g[s]%P*f[ful^s]%P);
	printf("%lld\n",Ans);
}
