#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXL=262144;
const int P=998244353;
const int g[]={3,(P+1)/3};

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

int rev[MAXL];
ll G[2][MAXL],f[MAXL],h[MAXL],fac[MAXL],ifac[MAXL],t[MAXL],t2[MAXL];

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<n)
		tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	return tot;
}

void NTT(ll *a,int n,int f)
{
	ll *ed=a+n;
	for(int i=0;i<n;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
		for(ll *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*G[f][MAXL/i*k]%P;
				x[k]=Add(u,t);y[k]=Sub(u,t);
			}
	if(f)
		for(int i=0,inv=ksm(n,P-2);i<n;i++)
			a[i]=a[i]*inv%P;
}

void Inv(ll *a,ll *res,int n)//f=2*f0+f^2g
{
	if(n==1)
		return res[0]=ksm(a[0],P-2),void();
	static ll t1[MAXL],t2[MAXL];
	int lim=(n+1)>>1;Inv(a,res,lim);
	int tot=init(2*n+5);
	memset(t1,0,sizeof(ll)*tot);
	memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++)
		t1[i]=a[i];
	for(int i=0;i<lim;i++)
		t2[i]=res[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++)
		t1[i]=(t2[i]*2-t1[i]*t2[i]%P*t2[i]%P+P)%P;
	NTT(t1,tot,1);
	for(int i=0;i<n;i++)
		res[i]=t1[i];
}

int main()
{
	G[0][0]=G[1][0]=1;
	G[0][1]=ksm(g[0],(P-1)/MAXL);
	G[1][1]=ksm(g[1],(P-1)/MAXL);
	for(int i=2;i<MAXL;i++)
		G[0][i]=G[0][i-1]*G[0][1]%P,
		G[1][i]=G[1][i-1]*G[1][1]%P;
	int N=1E5,T,n;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[N]=ksm(fac[N],P-2);
	for(int i=N-1;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=N;i++)
		t[i]=P-ifac[i];
	t[0]=1;
	int tot=init(2*N+2);
	NTT(t,tot,0);
	for(int i=0;i<tot;i++)
		t2[i]=t[i]*t[i]%P;
	NTT(t,tot,1);NTT(t2,tot,1);
	Inv(t,f,N+1);Inv(t2,h,N+1);
	memset(t,0,sizeof t);
	for(int i=1;i<=N;i++)
		t[i]=ifac[i];
	NTT(t,tot,0);NTT(f,tot,0);NTT(h,tot,0);
	for(int i=0;i<tot;i++)
		f[i]=f[i]*t[i]%P,
		h[i]=h[i]*t[i]%P;
	NTT(f,tot,1);NTT(h,tot,1);
	for(int i=1;i<=N;i++)
		f[i]=ksm(f[i],P-2);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%lld\n",h[n]*f[n]%P);
	}
}
