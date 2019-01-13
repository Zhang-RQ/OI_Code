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

const int MAXN=264145<<2;
const int P=998244353;
const int g[]={3,(P+1)/3};

int rev[MAXN],A[MAXN],B[MAXN],n,m,t;
ll fac[MAXN],ifac[MAXN],a[MAXN],b[MAXN],f[MAXN];

ll ksm(ll a,ll b)
{
	ll ret=1;a%=P;
	for(;b;b>>=1,(a*=a)%=P) if(b&1) (ret*=a)%=P;
	return ret;
}

ll inc(ll x,ll y){x+=y;return x>=P?x-P:x;}
ll dec(ll x,ll y){x-=y;return x<0?x+P:x;}

namespace poly_Mul{ll t1[MAXN],t2[MAXN],t3[MAXN],t4[MAXN];}
namespace poly_Inv{ll t1[MAXN],t2[MAXN];}
namespace poly_Ln{ll t1[MAXN],t2[MAXN],t3[MAXN];}

template<typename T> //RandomAccessIterator
	void NTT(T a,int n,int f)
	{
	    for(int i=0;i<n;i++)
	        if(i>rev[i])
	        	swap(a[i],a[rev[i]]);
	    for(int	i=2;i<=n;i<<=1)
	    {
	        ll wn=ksm(g[f],(P-1)/i);
	        for(int j=0;j<n;j+=i)
	        {
	            ll w=1;
	            for(int k=0;k<(i>>1);k++)
	            {
	                ll u=a[j+k],t=a[j+k+(i>>1)]*w%P;
	                a[j+k]=inc(u,t);a[j+k+(i>>1)]=dec(u,t);
	                w=w*wn%P;
	            }
	        }
	    }
	}

template<typename T1,typename T2,typename T3> //RandomAccessIterator no size check
	void Mul(T1 a,T2 b,T3 Res,int n,int m)
	{
		using namespace poly_Mul;
		int tot=1,lg2=0;
		while(tot<n+m) tot<<=1,lg2++;
		for(int i=0;i<tot;i++)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
		memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
		for(int i=0;i<n;i++) t1[i]=a[i];
		for(int i=0;i<m;i++) t2[i]=b[i];
		NTT(t1,tot,0);NTT(t2,tot,0);
		for(int i=0;i<tot;i++) t3[i]=t1[i]*t2[i]%P;
		NTT(t3,tot,1);
		ll inv=ksm(tot,P-2);
		for(int i=0;i<n+m-1;i++) Res[i]=inv*t3[i]%P;
	}

void Mul(ll *a,ll *b,ll *c,ll *Res,int n)
{
	using namespace poly_Mul;
	int tot=1,lg2=0;
	while(tot<2*n) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	memset(t1,0,sizeof(ll)*tot);memset(t2,0,sizeof(ll)*tot);
	memset(t3,0,sizeof(ll)*tot);
	for(int i=0;i<n;i++) t1[i]=a[i],t2[i]=b[i],t3[i]=c[i];
	NTT(t1,tot,0);NTT(t2,tot,0);NTT(t3,tot,0);
	for(int i=0;i<tot;i++) t4[i]=t1[i]*t2[i]%P*t3[i]%P;
	NTT(t4,tot,1);
	ll inv=ksm(tot,P-2);
	for(int i=0;i<tot;i++) Res[i]=inv*t4[i]%P;
}

vector<ll> operator * (const vector<ll> &lhs,const vector<ll> &rhs)
{
	int len=lhs.size()+rhs.size()-1;
	vector<ll> Ret(len);
	Mul(lhs.begin(),rhs.begin(),Ret.begin(),lhs.size(),rhs.size());
	return Ret;
}

vector<ll> solve(int *a,int l,int r)
{
	if(l==r) return vector<ll>({1,a[l]});
	int mid=(l+r)>>1;
	return solve(a,l,mid)*solve(a,mid+1,r);
}

template<typename T> //RandomAccessIterator
	void Deriv(T a,int n)
	{
		for(int i=0;i<=n-2;i++)
			a[i]=a[i+1]*(i+1)%P;
		a[n-1]=0;
	}


template<typename T> //RandomAccessIterator
	void Integ(T a,int n)
		{
			for(int i=n-1;~i;i--)
				a[i]=a[i-1]*ksm(i,P-2)%P;
			a[0]=0;
		}

void Inv(ll *a,ll *Res,int n)
{
	using namespace poly_Inv;
	memset(Res,0,sizeof(ll)*(n<<1));
	int l=1;
	Res[0]=ksm(a[0],P-2);
	while(l<n)
	{
		l<<=1;
		for(int i=0;i<l;i++) t1[i]=inc(Res[i],Res[i]);
		Mul(Res,Res,a,t2,l);
		for(int i=0;i<l;i++) Res[i]=dec(t1[i],t2[i]);
	}
}

vector<ll> Ln(const vector<ll> &a,int n)
{
	using namespace poly_Ln;
	vector<ll> Ret(2*n);
	memset(t1,0,sizeof(ll)*n);memset(t2,0,sizeof(ll)*n);
	for(int i=0;i<min(n,(int)a.size());i++) t1[i]=a[i],t2[i]=a[i];
	Deriv(t1,n);Inv(t2,t3,n);
	Mul(t1,t3,Ret.begin(),n,n);
	Integ(Ret.begin(),n);
	return Ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=m;i++) scanf("%d",&B[i]);
	scanf("%d",&t);
	int len=max(max(n,m),t),lena=max(n,t),lenb=max(m,t);
	fac[0]=ifac[0]=1;
	for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%P;
	ifac[len]=ksm(fac[len],P-2);
	for(int i=len-1;i;i--) ifac[i]=ifac[i+1]*(i+1)%P;
	vector<ll> la=Ln(solve(A,1,n),max(n,t)+1),lb=Ln(solve(B,1,m),max(m,t)+1);
	for(int i=1;i<=lena;i++) la[i]=i&1?i*la[i]%P:dec(0,i*la[i]%P);
	for(int i=1;i<=lenb;i++) lb[i]=i&1?i*lb[i]%P:dec(0,i*lb[i]%P);
	a[0]=n;b[0]=m;
	for(int i=1;i<=t;i++) a[i]=la[i]*ifac[i]%P;
	for(int i=1;i<=t;i++) b[i]=lb[i]*ifac[i]%P;
	Mul(a,b,f,t+1,t+1);
	ll inv=ksm(1ll*n*m%P,P-2);
	for(int i=1;i<=t;i++) printf("%lld\n",f[i]*fac[i]%P*inv%P);
}