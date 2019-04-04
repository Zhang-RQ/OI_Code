#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=1234567891;
const int MAXK=5010;

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

int k,DEG;
ll fac[MAXK],ifac[MAXK],pre[MAXK],suf[MAXK],n,a,d;
ll f[MAXK],g[MAXK],F[MAXK],G[MAXK],h[MAXK],H[MAXK],Hx[MAXK];

ll Calc(ll x,ll *poly,int deg) //f[1..deg] Real deg is deg-1
{
	x%=P;pre[0]=suf[deg+1]=1;
	for(int i=1;i<=deg;i++)
		pre[i]=pre[i-1]*Sub(x,i)%P;
	for(int i=deg;i;i--)
		suf[i]=suf[i+1]*Sub(x,i)%P;
	ll Ret=0;
	for(int i=1;i<=deg;i++)
		if((deg-i)&1)
			Ret=(Ret-poly[i]*pre[i-1]%P*suf[i+1]%P*ifac[deg-i]%P*ifac[i-1]%P+P)%P;
		else
			Ret=(Ret+poly[i]*pre[i-1]%P*suf[i+1]%P*ifac[deg-i]%P*ifac[i-1])%P;
	return Ret;
}

void solve()
{
	scanf("%d%lld%lld%lld",&k,&a,&n,&d);
	DEG=k+10;
	for(int i=1;i<=DEG;i++)
		f[i]=Add(f[i-1],ksm(i,k));
	for(int i=1;i<=DEG;i++)
		F[i]=Add(F[i-1],f[i]);
	for(int i=1;i<=DEG;i++)
		g[i]=Calc(i+a,f,DEG);
	for(int i=1;i<=DEG;i++)
		G[i]=Add(G[i-1],g[i]);
	ll lst=Calc(d,G,DEG);
	for(int i=1;i<=DEG;i++)
	{
		ll tmp=Calc((d+1ll*i*d)%P,G,DEG);
		h[i]=Sub(tmp,lst);
		lst=tmp;
	}
	for(int i=1;i<=DEG;i++)
		H[i]=Add(H[i-1],h[i]);
	for(int i=1;i<=DEG;i++)
		Hx[i]=Add(Hx[i-1],i*h[i]%P);
	ll Ans=Add((n+1)*Calc(a,F,DEG)%P,(n+1)*Calc(1ll*n*d%P,G,DEG)%P);
	Dec(Ans,Calc(n-1,Hx,DEG));Dec(Ans,Add(Calc(n-1,H,DEG),Calc(0,h,DEG)));
	printf("%lld\n",Ans);
}

int main()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<MAXK;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[MAXK-1]=ksm(fac[MAXK-1],P-2);
	for(int i=MAXK-2;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	int T;
	for(scanf("%d",&T);T--;solve());
}
