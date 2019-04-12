#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int MAXL=262144;
const ld PI=std::acos(-1);
const int lim=(1<<15)-1;

struct Complex{
	ld real,imag;

	Complex(ld _a=0,ld _b=0){real=_a;imag=_b;}

	Complex operator + (const Complex &rhs) const {return Complex(real+rhs.real,imag+rhs.imag);}
	Complex operator - (const Complex &rhs) const {return Complex(real-rhs.real,imag-rhs.imag);}
	Complex operator * (const double &rhs) const {return Complex(real*rhs,imag*rhs);}
	Complex operator * (const Complex &rhs) const {return Complex(real*rhs.real-imag*rhs.imag,real*rhs.imag+imag*rhs.real);}
	friend Complex conj(const Complex &rhs) {return Complex(rhs.real,-rhs.imag);}
}G[2][MAXL];

int rev[MAXL],P,n,m,a[MAXL],b[MAXL],c[MAXL];

int init(int n)
{
	int tot=1,lg2=0;
	while(tot<n) tot<<=1,lg2++;
	for(int i=0;i<tot;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg2-1));
	return tot;
}


void FFT(Complex *a,int n,int f)
{
	Complex *ed=a+n;
	for(int i=0;i<n;i++)
		if(i>rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=2;i<=n;i<<=1)
		for(Complex *x=a,*y=a+(i>>1);x!=ed;x+=i,y+=i)
			for(int k=0;k<(i>>1);k++)
			{
				Complex u=x[k],t=y[k]*G[f][MAXL/i*k];
				x[k]=u+t;y[k]=u-t;
			}
}

void Mul(int *a,int *b,int *Res,int l1,int l2)
{
	static Complex t1[MAXL],t2[MAXL],t3[MAXL],t4[MAXL];
	static Complex t5[MAXL],t6[MAXL],t7[MAXL],t8[MAXL];
	int tot=init(l1+l2);
	for(int i=0;i<l1;i++)
		t1[i]=Complex(a[i]>>15,a[i]&lim);
	for(int i=0;i<l2;i++)
		t2[i]=Complex(b[i]>>15,b[i]&lim);
	for(int i=l1;i<tot;i++)
		t1[i]=Complex(0,0);
	for(int i=l2;i<tot;i++)
		t2[i]=Complex(0,0);
	FFT(t1,tot,0);FFT(t2,tot,0);
	Complex Coef1(0.5,0),Coef2(0,-0.5);
	for(int i=0;i<tot;i++)
	{
		int j=(tot-i)&(tot-1);
		Complex A1=(t1[i]+conj(t1[j]))*Coef1;
		Complex A2=(t1[i]-conj(t1[j]))*Coef2;
		Complex B1=(t2[i]+conj(t2[j]))*Coef1;
		Complex B2=(t2[i]-conj(t2[j]))*Coef2;
		t5[i]=A1*B1;t6[i]=B2*A1;
		t7[i]=B1*A2;t8[i]=A2*B2;
	}
	for(int i=0;i<tot;i++)
		t3[i]=t5[i]+t6[i]*Complex(0,1),
		t4[i]=t7[i]+t8[i]*Complex(0,1);
	FFT(t3,tot,1);FFT(t4,tot,1);
	for(int i=0;i<tot;i++)
	{
		ll A=((ll)(t3[i].real/tot+0.5))%P,B=((ll)(t3[i].imag/tot+0.5))%P;
		ll C=((ll)(t4[i].real/tot+0.5))%P,D=((ll)(t4[i].imag/tot+0.5))%P;
		Res[i]=((A<<30)+(B<<15)+(C<<15)+D)%P;
	}
}
	
int main()
{
	for(int i=0;i<MAXL;i++)
		G[0][i]=Complex(std::cos(2*PI/MAXL*i),std::sin(2*PI/MAXL*i)),
		G[1][i]=Complex(std::cos(2*PI/MAXL*i),-std::sin(2*PI/MAXL*i));
	scanf("%d%d%d",&n,&m,&P);
	for(int i=0;i<=n;i++)
		scanf("%d",&a[i]),a[i]%=P;
	for(int i=0;i<=m;i++)
		scanf("%d",&b[i]),b[i]%=P;
	Mul(a,b,c,n+1,m+1);
	for(int i=0;i<=n+m;i++)
		printf("%d%c",c[i],"\n "[i!=n+m]);
}
