#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXN=1048576;
const int inv2=(P+1)>>1;
const int inv4=1ll*inv2*inv2%P;

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
	b=(b+P-1)%(P-1);
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int f[MAXN],t[MAXN],n;

void FWT(int *a,int n)
{
	for(int i=2;i<=n;i<<=1)
		for(int j=0;j<n;j+=i)
			for(int k=0;k<(i>>1);k++)
			{
				int x=a[j+k],y=a[j+k+(i>>1)];
				a[j+k]=Add(x,y);
				a[j+k+(i>>1)]=Sub(x,y);
			}
}

void IFWT(int *a,int n)
{
	for(int i=2;i<=n;i<<=1)
		for(int j=0;j<n;j+=i)
			for(int k=0;k<(i>>1);k++)
			{
				int x=a[j+k],y=a[j+k+(i>>1)];
				a[j+k]=1ll*Add(x,y)*inv2%P;
				a[j+k+(i>>1)]=1ll*Sub(x,y)*inv2%P;
			}
}

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),f[x]+=2,f[0]++;
	FWT(f,MAXN);
	assert(inv4*4ll%P==1);
	for(int i=0;i<MAXN;i++)
	{
		ll x=1ll*Sub(3*n,f[i])*inv4%P;
		t[i]=1ll*ksm(3,n-x)*ksm(P-1,x)%P;
	}
	IFWT(t,MAXN);
	printf("%d\n",Sub(t[0],1));
}
