#include<bits/stdc++.h>

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

const int MAXK=4E5+10;

int P,g;
vector<int> prs;

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

bool chk(int _g)
{
	for(int val:prs)
		if(ksm(_g,(P-1)/val)==1)
			return false;
	return true;
}

void find_g()
{
	int x=P-1;
	for(int i=2;i*i<=P-1;i++)
		if(!(x%i))
		{
			prs.push_back(i);
			while(!(x%i))
				x/=i;
		}
	if(x!=1)
		prs.push_back(x);
	for(int i=2;!g;i++)
		if(chk(i))
			g=i;
}

namespace Anymodule_Convolution{
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
	
	Complex t1[MAXL],t2[MAXL],t3[MAXL],t4[MAXL];
	Complex t5[MAXL],t6[MAXL],t7[MAXL],t8[MAXL];
	int rev[MAXL];

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

	void Mul(ll *a,ll *b,ll *Res,int l1,int l2)
	{
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

	void preworks()
	{
		for(int i=0;i<MAXL;i++)
			G[0][i]=Complex(std::cos(2*PI/MAXL*i),std::sin(2*PI/MAXL*i)),
			G[1][i]=Complex(std::cos(2*PI/MAXL*i),-std::sin(2*PI/MAXL*i));
	}
}

struct Mat{
	ll a[3][3];

	Mat(){memset(a,0,sizeof a);}

	ll* operator[] (int x){return a[x];}

	const ll* operator [] (int x) const {return a[x];}
	
	Mat operator + (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				ret[i][j]=Add(a[i][j],rhs[i][j]);
		return ret;
	}
	
	Mat operator * (const Mat &rhs) const
	{
		Mat ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					ret[i][j]+=a[i][k]*rhs[k][j]%P;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				ret[i][j]%=P;
		return ret;
	}

	Mat operator * (const ll &rhs) const
	{
		Mat ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				ret[i][j]=a[i][j]*rhs%P;
		return ret;
	}
}W,f[MAXK],I;

Mat ksm(Mat a,ll b)
{
	Mat ret=I;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			ret=ret*a;
	return ret;
}

int n,k,L,x,y;
ll wn[MAXK],t1[MAXK],h[MAXK],tmp[MAXK];

int C2(int x){return 1ll*x*(x-1)/2%k;}

int main()
{
	Anymodule_Convolution::preworks();
	I[0][0]=I[1][1]=I[2][2]=1;
	scanf("%d%d%d%d%d%d",&n,&k,&L,&x,&y,&P);
	--x;--y;find_g();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%lld",&W[i][j]);
	wn[0]=1;wn[1]=ksm(g,(P-1)/k);
	for(int i=2;i<k;i++)
		wn[i]=wn[i-1]*wn[1]%P;
	for(int i=0;i<k;i++)
		f[i]=ksm(W*wn[i]+I,L)*wn[C2(i)];
	reverse(f,f+k);
	for(int i=0;i<2*k;i++)
		h[i]=wn[(k-C2(i))%k];
	int inv=ksm(k,P-2);
	for(int l=0;l<k;l++)
		t1[l]=f[l][x][y];
	Anymodule_Convolution::Mul(t1,h,tmp,k,2*k);
	for(int l=0;l<k;l++)
		printf("%lld\n",tmp[l+k-1]*inv%P*wn[C2(l)]%P);
}
