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

const int MAXN=524299;
const double PI=acos(-1);

struct Complex{
	long double real,imag;

	Complex(long double _real=0,long double _imag=0){real=_real;imag=_imag;}

	Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
	Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
	Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
}t1[MAXN],t2[MAXN],t3[MAXN];

int rev[MAXN],n,x;
ll f[MAXN],g[MAXN],Ans[MAXN],p;

void FFT(Complex *a,int n,int f)
{
	for(int i=0;i<n;i++)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
	{
		Complex wn=Complex(cos(2*PI/i),f*sin(2*PI/i));
		for(int j=0;j<n;j+=i)
		{
			Complex w=Complex(1,0);
			for(int k=0;k<(i>>1);k++)
			{
				Complex u=a[j+k],t=w*a[j+k+(i>>1)];
				a[j+k]=u+t;a[j+k+(i>>1)]=u-t;
				w=w*wn;
			}
		}
	}
}

void multiply(ll *a,ll *b,ll *Res,int n)
{
	int lg2=0,tot=1;
	while(tot<(2*n)) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	for(int i=0;i<n;i++) t1[i]=Complex(a[i],0);
	for(int i=0;i<n;i++) t2[i]=Complex(b[i],0);
	for(int i=n;i<tot;i++) t1[i]=t2[i]=Complex();
	FFT(t1,tot,1);FFT(t2,tot,1);
	for(int i=0;i<tot;i++)
		t3[i]=t1[i]*t2[i];
	FFT(t3,tot,-1);
	for(int i=0;i<tot;i++)
		Res[i]=(ll)(t3[i].real/tot+0.5);
}

int main()
{
	scanf("%d%d",&n,&x);
	f[0]++;
	int lst=0;
	for(int i=1,t,s=0;i<=n;i++)
	{
		scanf("%d",&t);
		if(t<x)
		{
			int l=i-lst-1;
			if(l>0) p+=1ll*l*(l+1)/2;
			lst=i;
		}
		s+=(t<x);
		f[s]++;
	}
	int l=n-lst;
	if(l>0) p+=1ll*l*(l+1)/2;
	for(int i=0;i<=n;i++)
		g[i]=f[n-i];
	multiply(f,g,Ans,n+1);
	Ans[n]=p;
	for(int i=n;i<=2*n;i++)
		printf("%lld%c",Ans[i],"\n "[i!=2*n]);
}