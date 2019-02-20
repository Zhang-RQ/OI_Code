#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cassert>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int MAXN=262144;
const int P=998244353;
const int g[]={3,(P+1)/3};

int rev[MAXN],n,m;
ll G[2][MAXN],a[MAXN],sum[MAXN],tmp[MAXN],f[MAXN],p[MAXN],h[MAXN],lnf[MAXN],sumf[MAXN],Ans[MAXN],fac[MAXN],ifac[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}

ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<n) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=rev[i>>1]>>1|((i&1)<<(lg2-1));
	return tot;
}

void NTT(ll *a,int n,int f)
{
	for(int i=0;i<n;i++) if(i>rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
	{
		for(ll *x=a,*y=a+(i>>1),*ed=a+n;x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				ll u=x[k],t=y[k]*G[f][MAXN/i*k]%P;
				x[k]=inc(u,t),y[k]=dec(u,t);
			}
	}
}

void Mul(ll *a,ll *b,ll *Res,int n)
{
	int tot=init(n<<1);
	static ll t1[MAXN],t2[MAXN];
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++) t1[i]=t1[i]*t2[i]%P;
	NTT(t1,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<tot;i++) Res[i]=t1[i]*inv%P;
}

void Inv(ll *a,ll *Res,int n)
{
	if(n==1) return Res[0]=ksm(a[0],P-2),void();
	Inv(a,Res,(n+1)>>1);
	int tot=init(n<<1),lst=(n+1)>>1;
	static ll t1[MAXN],t2[MAXN];
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++) t1[i]=a[i];
	for(int i=0;i<lst;i++) t2[i]=Res[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++) t1[i]=dec(2*t2[i],t2[i]*t2[i]%P*t1[i]%P);
	NTT(t1,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<n;i++) Res[i]=t1[i]*inv%P;
}

void derivation(ll *f,int n)
{
    for(int i=0;i<n-1;i++) f[i]=f[i+1]*(i+1)%P;
    f[n-1]=0;
}

void integral(ll *f,int n)
{
    for(int i=n-1;~i;i--) f[i]=f[i-1]*ksm(i,P-2)%P;
    f[0]=0;
}

void Ln(ll *a,ll *Res,int n)
{
	static ll t1[MAXN],t2[MAXN];
	for(int i=0;i<n;i++) t1[i]=a[i];
	Inv(t1,t2,n);
	derivation(t1,n);
	Mul(t1,t2,Res,n);
	integral(Res,n);
}

void Exp(ll *a,ll *Res,int n)
{
	if(n==1) return Res[0]=1,void();
	Exp(a,Res,(n+1)>>1);
	static ll t1[MAXN],t2[MAXN],t3[MAXN];
	int tot=init(n<<1),lst=(n+1)>>1;
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	memset(t3,0,sizeof(ll)*tot);
	Ln(Res,t1,n);
	for(int i=0;i<n;i++) t2[i]=a[i];
	for(int i=0;i<lst;i++) t3[i]=Res[i];
	NTT(t1,tot,0);NTT(t2,tot,0);NTT(t3,tot,0);
	for(int i=0;i<tot;i++) t1[i]=dec(t2[i]+1,t1[i])*t3[i]%P;
	NTT(t1,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<n;i++) Res[i]=t1[i]*inv%P;
}

vector<ll> solve(int l,int r)
{
	if(l==r) return vector<ll>({1,dec(0,a[l])});
	int mid=(l+r)>>1,lenl=mid-l+1,lenr=r-mid;
	vector<ll> L=solve(l,mid),R=solve(mid+1,r),Ret;
	Ret.resize(r-l+2);
	int tot=init(r-l+2);
	static ll t1[MAXN],t2[MAXN];
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	for(int i=0;i<=lenl;i++) t1[i]=L[i];
	for(int i=0;i<=lenr;i++) t2[i]=R[i];
	NTT(t1,tot,0);NTT(t2,tot,0);
	for(int i=0;i<tot;i++) t1[i]=t1[i]*t2[i]%P;
	NTT(t1,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<r-l+2;i++) Ret[i]=t1[i]*inv%P;
	return Ret;
}

int main()
{
	fac[0]=ifac[0]=1;
	G[0][0]=G[1][0]=1;
	G[0][1]=ksm(g[0],(P-1)/MAXN);
	G[1][1]=ksm(g[1],(P-1)/MAXN);
	for(int i=2;i<MAXN;i++)
		G[0][i]=G[0][i-1]*G[0][1]%P,G[1][i]=G[1][i-1]*G[1][1]%P;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
	ifac[n]=ksm(fac[n],P-2);
	for(int i=n-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	vector<ll> t=solve(1,n);
	for(int i=0;i<=n;i++) tmp[i]=t[i];
	Ln(tmp,sum,n+1);sum[0]=n;
	for(int i=1;i<=n;i++) sum[i]=dec(0,sum[i])*i%P;
	for(int i=0;i<n;i++) f[i]=ksm(i+1,m)*ifac[i]%P;
	for(int i=0;i<n;i++) h[i]=ksm(i+1,2*m)*ifac[i]%P;
	Inv(f,p,n);
	Mul(p,h,p,n);
	Ln(f,lnf,n);
	for(int i=0;i<n;i++) lnf[i]=lnf[i]*sum[i]%P;
	Exp(lnf,sumf,n);
	for(int i=0;i<n;i++) p[i]=p[i]*sum[i]%P;
	Mul(p,sumf,Ans,n);
	ll prod=1;
	for(int i=1;i<=n;i++) prod=prod*a[i]%P;
	printf("%lld\n",Ans[n-2]*prod%P*fac[n-2]%P);
}
