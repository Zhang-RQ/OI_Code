#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=262145;
const int P=998244353;
const int g=3;

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

int rev[MAXN],inv[MAXN];

void init_rev(int n,int lg2)
{
	for(int i=0;i<n;i++)
		rev[i]=rev[i>>1]>>1|((i&1)<<(lg2-1));
}

ll inc(ll a,ll b){a+=b;return a>P?a-P:a;}

ll dec(ll a,ll b){a-=b;return a<0?a+P:a;}

void clear(ll *a,int n)
{
	int t=1;
	while(t<n) t<<=1;
	memset(a+t,0,sizeof(ll)*(t-n));
}

void clear_all(ll *a,int n)
{
	int t=1;
	while(t<n) t<<=1;
	memset(a,0,sizeof(ll)*t);
}

void NTT(ll *a,int n,int f)
{
	for(int i=0;i<n;i++)
		if(i>rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
	{
		ll wn=ksm(g,f?(P-1)/i:P-1-(P-1)/i);
		for(int j=0;j<n;j+=i)
		{
			ll w=1;
			for(int k=0;k<(i>>1);k++)
			{
				ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
				a[j+k]=inc(u,t);
				a[j+k+(i>>1)]=dec(u,t);
				w=w*wn%P;
			}
		}
	}
}

namespace Poly_multiply{ll t1[MAXN],t2[MAXN],t3[MAXN];}
namespace Poly_inverse{ll t1[MAXN],t2[MAXN];}
namespace Poly_ln{ll t1[MAXN],t2[MAXN];}
namespace Poly_exp{ll t1[MAXN],t2[MAXN];}

void multiply (ll *a,ll *b,ll *Res,int n)
{
	using namespace Poly_multiply;
	int tot=1,lg2=0;
	while(tot<(n<<1)) tot<<=1,++lg2;
	for(int i=0;i<tot;i++) t1[i]=t2[i]=0;
	for(int i=0;i<n;i++) t1[i]=a[i];
	for(int i=0;i<n;i++) t2[i]=b[i];
	init_rev(tot,lg2);
	NTT(t1,tot,1);NTT(t2,tot,1);
	for(int i=0;i<tot;i++) Res[i]=t1[i]*t2[i]%P;
	NTT(Res,tot,0);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<tot;i++) Res[i]=Res[i]*inv%P;
}

void multiply(ll *a,ll *b,ll *c,ll *Res,int n)
{
	using namespace Poly_multiply;
	int tot=1,lg2=0;
	while(tot<(n<<1)) tot<<=1,++lg2;
	for(int i=0;i<tot;i++) t1[i]=t2[i]=t3[i]=0;
	for(int i=0;i<n;i++) t1[i]=a[i];
	for(int i=0;i<n;i++) t2[i]=b[i];
	for(int i=0;i<n;i++) t3[i]=c[i];
	init_rev(tot,lg2);
	NTT(t1,tot,1);NTT(t2,tot,1);NTT(t3,tot,1);
	for(int i=0;i<tot;i++) Res[i]=t1[i]*t2[i]%P*t3[i]%P;
	NTT(Res,tot,0);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<tot;i++) Res[i]=Res[i]*inv%P;
}
	
void inverse(ll *a,ll *Res,int n)//notice Res is empty & a don't have anything upper than n
{
	using namespace Poly_inverse;
	int l=1;
	clear_all(Res,n);clear_all(t1,n);clear_all(t2,n);
	Res[0]=ksm(a[0],P-2);
	while(l<n)
	{
		for(int i=0;i<l;i++) t2[i]=2*Res[i]%P;
		l<<=1;
		multiply(Res,Res,a,t1,l);
		for(int i=0;i<l;i++) Res[i]=dec(t2[i],t1[i]);
	}
}

void Deriv(ll *a,int n)
{
	for(int i=0;i<n-1;i++)
		a[i]=a[i+1]*(i+1)%P;
	a[n-1]=0;
}

void Integ(ll *a,int n)
{
	for(int i=n;~i;i--)
		a[i]=a[i-1]*inv[i]%P;
	a[0]=0;
}

void ln(ll *a,ll *Res,int n)
{
	using namespace Poly_ln;
	clear(a,n);clear_all(t1,n);clear_all(t2,n);
	for(int i=0;i<n;i++) t1[i]=a[i];
	inverse(a,t2,n);
	Deriv(t1,n);
	multiply(t2,t1,Res,n);
	Integ(Res,n-1);
}

void exp(ll *a,ll *Res,int n)
{
	using namespace Poly_exp;
	clear_all(Res,n);
	clear_all(t1,n);
	clear_all(t2,n);
	int l=1;
	Res[0]=1;
	while(l<(n<<1))
	{
		ln(Res,t2,l);
		for(int i=0;i<l;i++) t1[i]=inc(i==0,dec(a[i],t2[i]));
		multiply(t1,Res,Res,l);l<<=1;
	}
}

int n;
ll f[MAXN],ff[MAXN],gg[MAXN];

int main()
{
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;i++) inv[i]=1ll*(P-P/i)*inv[P%i]%P;
	for(int i=0;i<n;i++) scanf("%lld",&f[i]);
	exp(f,ff,n);
	for(int i=0;i<n;i++) printf("%lld%c",ff[i],"\n "[i!=n-1]);
}

