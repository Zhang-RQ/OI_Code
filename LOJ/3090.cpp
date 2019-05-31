#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int P=998244353;
const int MAXK=505;

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

template<int C>
struct Complex {
	int a,b; //a+bsqrt(C)
	
	Complex(int _a=0,int _b=0){a=_a;b=_b;}

	Complex operator + (const Complex &rhs) const {return Complex(Add(a,rhs.a),Add(b,rhs.b));}
	Complex operator - (const Complex &rhs) const {return Complex(Sub(a,rhs.a),Sub(b,rhs.b));}
	Complex operator * (const Complex &rhs) const {return Complex(Add(1ll*a*rhs.a%P,1ll*C*b%P*rhs.b%P),Add(1ll*a*rhs.b%P,1ll*b*rhs.a%P));}

	Complex inv() const
	{
		ll d=ksm(Sub(1ll*a*a%P,1ll*C*b%P*b%P),P-2);
		return Complex(1ll*a*d%P,P-1ll*b*d%P);
	}
};

template<int C>
Complex<C> ksm(Complex<C> a,ll b)
{
	Complex<C> ret(1,0);
	for(;b;b>>=1,a=a*a)
		if(b&1)
			ret=ret*a;
	return ret;
}

int m;
ll S[MAXK][MAXK],C[MAXK][MAXK],fac[MAXK],ifac[MAXK];

void solve2()
{
	int k;
	ll l,r;
	scanf("%lld%lld%d",&l,&r,&k);
	ll Ans=0,inv10=ksm(10,P-2),inv2=ksm(2,P-2);
	for(int j=0;j<=k;j++)
		for(int a=0;a<=j;a++)
		{
			ll coef=((k-j)&1?(P-1):1)*S[k][j]%P*C[j][a]%P;
			Complex<5> x=ksm(Complex<5>(inv2,inv10),a),y=ksm(Complex<5>(inv2,P-inv10),j-a);
			Complex<5> q=ksm(Complex<5>(inv2,inv2),a)*ksm(Complex<5>(inv2,P-inv2),j-a),pw;
			if(q.a==1&&q.b==0)
				pw=Complex<5>((r-l+1)%P,0);
			else
				pw=(ksm(q,r-l+1)-Complex<5>(1,0))*(q-Complex<5>(1,0)).inv();
			Complex<5> tAns=x*y*ksm(q,l)*pw;
			Inc(Ans,tAns.a*coef%P);
		}
	Ans=Ans*ifac[k]%P*ksm((r-l+1)%P,P-2)%P;
	printf("%lld\n",Ans);
}

void solve3()
{
	int k;
	ll l,r;
	scanf("%lld%lld%d",&l,&r,&k);
	ll Ans=0,inv6=ksm(6,P-2),inv2=ksm(2,P-2),L=(l+1)>>1,R=r>>1;
	for(int j=0;j<=k;j++)
		for(int a=0;a<=j;a++)
		{
			ll coef=((k-j)&1?(P-1):1)*S[k][j]%P*C[j][a]%P;
			Complex<3> x=ksm(Complex<3>(inv2,inv6),a),y=ksm(Complex<3>(inv2,P-inv6),j-a);
			Complex<3> q=ksm(Complex<3>(2,1),a)*ksm(Complex<3>(2,P-1),j-a),pw;
			if(q.a==1&&q.b==0)
				pw=Complex<3>((R-L+1)%P,0);
			else
				pw=(ksm(q,R-L+1)-Complex<3>(1,0))*(q-Complex<3>(1,0)).inv();
			Complex<3> tAns=x*y*ksm(q,L)*pw;
			Inc(Ans,tAns.a*coef%P);
		}
	Ans=Ans*ifac[k]%P*ksm((r-l+1)%P,P-2)%P;
	printf("%lld\n",Ans);
	
}

int main()
{
	S[0][0]=1;C[0][0]=1;fac[0]=ifac[0]=1;
	for(int i=1;i<=501;i++)
		fac[i]=fac[i-1]*i%P;
	ifac[501]=ksm(fac[501],P-2);
	for(int i=500;i;i--)
		ifac[i]=ifac[i+1]*(i+1)%P;
	for(int i=1;i<=501;i++)
	{
		S[i][0]=0;C[i][0]=1;
		for(int j=1;j<=i;j++)
			S[i][j]=Add(S[i-1][j-1],1ll*(i-1)*S[i-1][j]%P),
			C[i][j]=Add(C[i-1][j-1],C[i-1][j]);
	}
	int T;
	scanf("%d%d",&T,&m);
	while(T--)
	{
		if(m==2)
			solve2();
		else
			solve3();
	}
}
