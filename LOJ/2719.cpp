#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=1.2E6+10;
const int L=1.2E6;
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

int n,a[MAXN],vis[MAXN];
ll fac[MAXN],ifac[MAXN];

ll C(int n,int m)
{
	if(n<m||n<0||m<0)
		return 0;
	return fac[n]*ifac[m]%P*ifac[n-m]%P;
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),vis[i]=0;
	ll Ans=0;vis[n+1]=0;
	int Mx=0,Mn=1;
	for(int i=1;i<=n;i++)
	{
		vis[a[i]]=1;
		if(a[i]>Mx)
			Mx=a[i];
		else
		{
			while(vis[Mn]&&Mn!=a[i])
				++Mn;
			if(a[i]!=Mn)
			{
				Inc(Ans,Sub(C(2*n-i-Mx,n-i+1),C(2*n-i-Mx,n-i+2)));
				break;
			}
			while(vis[Mn])
				++Mn;
		}
		//(i-1,Mx+1)->(n,n)
		Inc(Ans,Sub(C(2*n-i-Mx,n-i+1),C(2*n-i-Mx,n-i+2)));
	}
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=L;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[L]=ksm(fac[L],P-2);
	for(int i=L-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(scanf("%d",&T);T--;solve());
}
